#include "Node.h"

//Pipeline Node::_pipeline;

Node::Node()
{
	parent = 0;
	translation = Vector3f(0.0f);
	rotation = Vector3f(0.0f);
	scale = Vector3f(1.0f);
	_pipeline = Pipeline();
	UpdateTransform(Matrix4f::Identity());
}

Node::~Node()
{
}


Model drawMe;
std::list<Node> _children;

void Node::AddChild(Node *newNode) {
	newNode->parent = this;
	_children.push_front(newNode);
}
void Node::RemoveChild(Node *oldNode) {
	//_children.remove(oldNode);
}
void Node::Draw(Matrix4f parentTransform) {
	UpdateTransform(parentTransform);

	for (std::list<Component*>::iterator iter = components.begin(); iter != components.end(); iter++) {
		(*iter)->Draw(transform);
	}

	//pass the draw call to the next node
	//passing along the transforms
	std::list<Node*>::iterator iter;
	for (iter = _children.begin(); iter != _children.end(); ++iter) {
		(*iter)->Draw(transform);
	}
}

void Node::AddComponent(Component* newComponent)
{
	components.push_back(newComponent);
	newComponent->myNode = this; 
}

void Node::Update(Matrix4f parentTransform)
{
	UpdateTransform(parentTransform);

	for (std::list<Component*>::iterator iter = components.begin(); iter != components.end(); iter++) {
		(*iter)->Update();
	}

	std::list<Node*>::iterator iter;
	for (iter = _children.begin(); iter != _children.end(); ++iter) {
		(*iter)->Update(transform);
	}
}

void Node::UpdateTransform(Matrix4f parentTransform)
{
	_pipeline.SetParentTrans(parentTransform);
	_pipeline.SetPosition(translation);
	_pipeline.SetRotation(rotation);
	_pipeline.SetScale(scale);
	transform = _pipeline.GetTransform();
	
	up = (Vector3f(0, 1, 0).RotateBy(transform)).Normalize();
	forward = (Vector3f(0, 0, 1).RotateBy(transform)).Normalize();
	right = (Vector3f(1, 0, 0).RotateBy(transform)).Normalize();
	worldPos = Vector3f(0.0f).TranslateBy(transform);
}