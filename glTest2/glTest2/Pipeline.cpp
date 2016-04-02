#include "Pipeline.h"
#include "ShaderManager.h"

Pipeline::Pipeline()
{
	SetScale(Vector3f());
	SetPosition(Vector3f());
	SetRotation(Vector3f());
}

Pipeline::Pipeline(Vector3f scale, Vector3f position, Vector3f rotation)
{
	SetScale(scale);
	SetPosition(position);
	SetRotation(rotation);
}

Pipeline::~Pipeline()
{
}

void Pipeline::SetScale(Vector3f scale)
{
	dirty = true;
	m_scale_trans.InitScaleTransform(scale);

}
void Pipeline::SetPosition(Vector3f position)
{
	dirty = true;
	m_position_trans.InitTranslationTransform(position);
}
void Pipeline::SetRotation(Vector3f rotation)
{
	dirty = true;
	m_rotate_trans.InitRotateTransform(rotation);
}
void Pipeline::SetParentTrans(Matrix4f parentTrans)
{
	dirty = true;
	m_parent_trans = parentTrans;
}

void Pipeline::CalculateTransform() {
	if (dirty) {
		dirty = false;
		//TODO: figure out why this line dosn't draw right
		//even when it gives the exact same matrix as below 
		//m_transformation = m_parent_trans *  m_position_trans * m_rotate_trans * m_scale_trans;
		m_transformation = Matrix4f::Identity();
	}
}

void Pipeline::Draw(GLuint &VBO, GLuint &IBO)
{
	CalculateTransform();
	//one day this needs to be more flexible to allow for many types of shaders
	glUniformMatrix4fv(ShaderManager::GetShaderUniform(shaderName, uniformName), 1, GL_TRUE, (const GLfloat*)m_transformation);
	//Matrix4f m = Matrix4f::Identity();
	//glUniformMatrix4fv(ShaderManager::GetShaderUniform(shaderName, uniformName), 1, GL_TRUE, (const GLfloat*)m);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);
}


Matrix4f Pipeline::GetTransform()
{
	CalculateTransform();
	return m_transformation;
}