#include "Model.h"
#include "Texture.h"
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

void Model::CreateVertexBuffer(Vertex vertices[], GLsizeiptr sizeofVertices)
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
	Texture::Bind(textureName);
	ShaderManager::UseShader(shaderName);
	//one day this needs to be more flexible to allow for many types of shaders
	glUniformMatrix4fv(ShaderManager::GetShaderUniform(shaderName, uniformName), 1, GL_TRUE, (const GLfloat*)transform);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//two attrib pointers now, one for vertecies and one for texture coordinates
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}