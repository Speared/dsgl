#include "Billboard.h"
#include "Texture.h"
#include "Node.h"


Billboard::Billboard()
{
	//create a new, square model and add it to our node
	myModel = new Model();
	Vertex Vertices[4] = { Vertex(Vector3f(-0.5f, -0.5f, 0.0f), Vector2f(0.0f, 0.0f)),
		Vertex(Vector3f(0.5f, -0.5f, 0.0f), Vector2f(0.5f, 0.0f)),
		Vertex(Vector3f(0.5f, 0.5f, 0.0f), Vector2f(1.0f, 0.0f)),
		Vertex(Vector3f(-0.5f, 0.5f, 0.0f),  Vector2f(0.5f, 1.0f)) };

	myModel->CreateVertexBuffer(Vertices, sizeof(Vertices));

	unsigned int Indices[] = { 0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2 };

	myModel->CreateIndexBuffer(Indices, sizeof(Indices));

	//myNode->AddComponent(myModel);
}

Billboard::~Billboard()
{
	delete myModel;
}

void Billboard::Draw(Matrix4f transform) {
	//there may be a better way to assign shader/uniform to the model than doing it every frame
	myModel->shaderName = shaderName;
	myModel->textureName = textureName;
	myModel->uniformName = uniformName;
	myModel->Draw(transform);
}