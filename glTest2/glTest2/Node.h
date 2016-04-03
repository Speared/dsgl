#pragma once
#include "math_3d.h"
#include "Model.h"
#include "Pipeline.h"
#include <list>
#include "Component.h"
#include "DrawableComponent.h"
class Node
{
public:
	Vector3f translation;
	Vector3f rotation;
	Vector3f scale;

	const char* name;

	void AddChild(Node *newNode);
	void RemoveChild(Node *oldNode);
	void Draw(Matrix4f parentTransform);


	void AddComponent(DrawableComponent* newComponent);
	void AddComponent(Component* newComponent);
	void UpdateComponents();

	std::list<Component*> components;
	std::list<DrawableComponent*> drawable_components;

	Node();
	~Node();
private:
	std::list<Node*> _children;
	Pipeline _pipeline;
};
