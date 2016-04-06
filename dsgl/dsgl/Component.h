#pragma once
#include "math_3d.h"
class Node;
class Component
{
public:
	Component();
	~Component();
	virtual void Update() {}
	virtual void Draw(Matrix4f transform) {}
	Node *myNode;
private:

};

