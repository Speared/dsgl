#include "Node.h"

//Pipeline Node::_pipeline;

Node::Node()
{
	translation = Vector3f(0.0f);
	rotation = Vector3f(0.0f);
	scale = Vector3f(1.0f);
	_pipeline = Pipeline();
}

Node::~Node()
{
}


Model drawMe;
std::list<Node> _children;

void Node::AddChild(Node *newNode) {
	_children.push_front(newNode);
}
void Node::RemoveChild(Node *oldNode) {
	//_children.remove(oldNode);
}
void Node::Draw(Matrix4f parentTransform) {
	
	const char* myname = name;

	_pipeline.SetParentTrans(parentTransform);
	_pipeline.SetPosition(translation);
	_pipeline.SetRotation(rotation);
	_pipeline.SetScale(scale);
	//GLuint VBO;
	//GLuint IBO;
	//drawMe.GetBuffers(VBO, IBO);
	//_pipeline.Draw(VBO, IBO);
	
	Matrix4f transform = _pipeline.GetTransform();

	for (std::list<DrawableComponent*>::iterator iter = drawable_components.begin(); iter != drawable_components.end(); iter++) {
		(*iter)->Draw(transform);
	}

	//pass the draw call to the next node
	//passing along the transforms
	std::list<Node*>::iterator iter;
	for (iter = _children.begin(); iter != _children.end(); ++iter) {
		(*iter)->Draw(transform);
	}
}

void Node::AddComponent(DrawableComponent* newComponent)
{
	drawable_components.push_back(newComponent);
	components.push_back(newComponent);
	newComponent->myNode = this;
}

void Node::AddComponent(Component* newComponent)
{
	components.push_back(newComponent);
	newComponent->myNode = this; 
}

void Node::UpdateComponents()
{
	for (std::list<Component*>::iterator iter = components.begin(); iter != components.end(); iter++) {
		(*iter)->Update();
	}
}
