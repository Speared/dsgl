#pragma once
//note to self: I never did the last bit of this tutorial
//http://ogldev.atspace.co.uk/www/tutorial16/tutorial16.html
//there's a chance this is still done totally wrong, dispite working
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
	const char* textureName;
private:
	GLuint VBO;
	GLuint IBO;
	
};

