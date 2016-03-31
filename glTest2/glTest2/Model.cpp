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

void Model::GetBuffers(GLuint& vbo, GLuint& ibo) {
	vbo = VBO;
	ibo = IBO;
}