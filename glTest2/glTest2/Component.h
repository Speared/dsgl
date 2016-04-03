#pragma once
class Node;
class Component
{
public:
	Component();
	~Component();
	virtual void Update() {}
	Node *myNode;
private:

};

