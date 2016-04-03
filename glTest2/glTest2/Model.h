#pragma once
#include <gl\glew.h>
#include <gl\glut.h>
#include "math_3d.h"
#include "ShaderManager.h"
#include "DrawableComponent.h"
class Model : public DrawableComponent
{
public:
	Model();
	~Model();

	//one day these functions should be private, and there should be a function that takes in a modle instead
	void CreateIndexBuffer(unsigned int indices[], GLsizeiptr sizeofIndices);
	void CreateVertexBuffer(Vector3f vertices[], GLsizeiptr sizeofVertices);
	void GetBuffers(GLuint& vbo, GLuint& ibo);
	void Draw(Matrix4f transform);
	
	//TODO: better system for this
	const char* shaderName;
	const char* uniformName;
private:
	GLuint VBO;
	GLuint IBO;
	
};

