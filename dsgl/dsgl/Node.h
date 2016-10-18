#pragma once
#include "math_3d.h"
#include "Model.h"
#include "Pipeline.h"
#include <list>
#include "Component.h"
class Node
{
public:
	Vector3f translation;
	Vector3f rotation;
	Vector3f scale;

	const char* name;
	Node* parent;

	void AddChild(Node *newNode);
	void RemoveChild(Node *oldNode);
	void Draw(Matrix4f parentTransform);
	void Update(Matrix4f parentTransform);

	void AddComponent(Component* newComponent);

	std::list<Component*> components;

	Matrix4f GetTransform() {
		return worldTransform;
	}

	Vector3f forward;
	Vector3f up;
	Vector3f right;
	Vector3f worldPos;

	//these values were being accidently calculated, I'm holding on to them for not just in case 
	Vector3f cameraForward;
	Vector3f cameraUp;
	Vector3f cameraRight;
	Vector3f cameraPos;

	Node();
	~Node();
private:
	void UpdateCameraTransform(Matrix4f parentTransform);
	void UpdateWorldTransform(Matrix4f parentTransform);
	Matrix4f worldTransform;
	Matrix4f cameraTransform;
	std::list<Node*> _children;
	Pipeline _pipeline;
};
