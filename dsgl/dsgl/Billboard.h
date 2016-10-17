#pragma once
#include "Component.h"
#include "Model.h"
//Bilboards need to be a square model with a texture that always faces the camera
class Billboard : public Component
{
public:
	Billboard();
	~Billboard();

	void Draw(Matrix4f transform);

	const char* shaderName;
	const char* uniformName;
	const char* textureName;
private:
	Model* myModel;
};