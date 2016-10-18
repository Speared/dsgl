#include "Node.h"

//Pipeline Node::_pipeline;

Node::Node()
{
	parent = 0;
	translation = Vector3f(0.0f);
	rotation = Vector3f(0.0f);
	scale = Vector3f(1.0f);
	_pipeline = Pipeline();
	UpdateWorldTransform(Matrix4f::Identity());
	UpdateCameraTransform(Matrix4f::Identity());
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
	UpdateCameraTransform(parentTransform);

	for (std::list<Component*>::iterator iter = components.begin(); iter != components.end(); iter++) {
		(*iter)->Draw(cameraTransform);
	}

	//pass the draw call to the next node
	//passing along the transforms
	std::list<Node*>::iterator iter;
	for (iter = _children.begin(); iter != _children.end(); ++iter) {
		(*iter)->Draw(cameraTransform);
	}
}

void Node::AddComponent(Component* newComponent)
{
	components.push_back(newComponent);
	newComponent->myNode = this; 
}

void Node::Update(Matrix4f parentTransform)
{
	UpdateWorldTransform(parentTransform);

	for (std::list<Component*>::iterator iter = components.begin(); iter != components.end(); iter++) {
		(*iter)->Update();
	}

	std::list<Node*>::iterator iter;
	for (iter = _children.begin(); iter != _children.end(); ++iter) {
		(*iter)->Update(worldTransform);
	}
}

void Node::UpdateCameraTransform(Matrix4f parentTransform)
{
	_pipeline.SetParentTrans(parentTransform);
	_pipeline.SetPosition(translation);
	_pipeline.SetRotation(rotation);
	_pipeline.SetScale(scale);
	cameraTransform = _pipeline.GetTransform();
	
	cameraUp = (Vector3f(0, 1, 0).RotateBy(cameraTransform)).Normalize();
	cameraForward = (Vector3f(0, 0, 1).RotateBy(cameraTransform)).Normalize();
	cameraRight = (Vector3f(1, 0, 0).RotateBy(cameraTransform)).Normalize();
	cameraPos = Vector3f(0.0f).TranslateBy(cameraTransform);
}

void Node::UpdateWorldTransform(Matrix4f parentTransform)
{
	_pipeline.SetParentTrans(parentTransform);
	_pipeline.SetPosition(translation);
	_pipeline.SetRotation(rotation);
	_pipeline.SetScale(scale);
	worldTransform = _pipeline.GetTransform();

	up = (Vector3f(0, 1, 0).RotateBy(worldTransform)).Normalize();
	forward = (Vector3f(0, 0, 1).RotateBy(worldTransform)).Normalize();
	right = (Vector3f(1, 0, 0).RotateBy(worldTransform)).Normalize();
	worldPos = Vector3f(0.0f).TranslateBy(worldTransform);
}