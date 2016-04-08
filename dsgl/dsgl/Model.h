#pragma once
#include <gl\glew.h>
#include <gl\glut.h>
#include "math_3d.h"
#include "ShaderManager.h"
#include "Component.h"
struct Vertex
{
	Vector3f position;
	Vector2f textureCoordinate;
	Vertex(Vector3f position, Vector2f textureCoordinate) :
		position(position), textureCoordinate(textureCoordinate) {}
};

class Model : public Component
{
public:
	Model();
	~Model();

	//one day these functions should be private, and there should be a function that takes in a modle instead
	void CreateIndexBuffer(unsigned int indices[], GLsizeiptr sizeofIndices);
	void CreateVertexBuffer(Vertex vertices[], GLsizeiptr sizeofVertices);
	void GetBuffers(GLuint& vbo, GLuint& ibo);
	void Draw(Matrix4f transform);
	
	//TODO: better system for this
	const char* shaderName;
	const char* uniformName;
private:
	GLuint VBO;
	GLuint IBO;
	
};

