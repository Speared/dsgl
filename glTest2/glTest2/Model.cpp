#include "Model.h"

Model::Model()
{
}

Model::~Model()
{
}

void Model::CreateIndexBuffer(unsigned int indices[], GLsizeiptr sizeofIndices)
{
	
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeofIndices, indices, GL_STATIC_DRAW);
	
}

void Model::CreateVertexBuffer(Vector3f vertices[], GLsizeiptr sizeofVertices)
{
	
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeofVertices, vertices, GL_STATIC_DRAW);
	
}

void Model::GetBuffers(GLuint& vbo, GLuint& ibo) 
{
	vbo = VBO;
	ibo = IBO;
}

void Model::Draw(Matrix4f transform) 
{
	//one day this needs to be more flexible to allow for many types of shaders
	glUniformMatrix4fv(ShaderManager::GetShaderUniform(shaderName, uniformName), 1, GL_TRUE, (const GLfloat*)transform);
	//Matrix4f m = Matrix4f::Identity();
	//glUniformMatrix4fv(ShaderManager::GetShaderUniform(shaderName, uniformName), 1, GL_TRUE, (const GLfloat*)m);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);
}