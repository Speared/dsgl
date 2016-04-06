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
		return transform;
	}

	Vector3f forward;
	Vector3f up;
	Vector3f right;

	Node();
	~Node();
private:
	void UpdateTransform(Matrix4f parentTransform);
	Matrix4f transform;
	std::list<Node*> _children;
	Pipeline _pipeline;
};
