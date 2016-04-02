#pragma once
#include "math_3d.h"
#include "Model.h"
#include "Pipeline.h"
#include <list>
class Node
{
public:
	Vector3f translation;
	Vector3f rotation;
	Vector3f scale;

	//one day this should be a gameobject
	//and the gameobject would have a model
	//and modle would have shader
	Model drawMe;
	char* shaderName;
	char* uniformName;

	void AddChild(Node &newNode);
	void RemoveChild(Node & oldNode);
	void Draw(Matrix4f parentTransform);

	Node();
	~Node();
private:
	std::list<Node> _children;
	Pipeline _pipeline;
};
