#include "Node.h"

//Pipeline Node::_pipeline;

Node::Node()
{
	translation = Vector3f(0.0f);
	rotation = Vector3f(0.0f);
	scale = Vector3f(0.0f);
	_pipeline = Pipeline();
}

Node::~Node()
{
}


Model drawMe;
std::list<Node> _children;

void Node::AddChild(Node &newNode) {
	_children.push_front(newNode);
}
void Node::RemoveChild(Node & oldNode) {
	//_children.remove(oldNode);
}
void Node::Draw(Matrix4f parentTransform) {
	_pipeline.SetParentTrans(parentTransform);
	_pipeline.SetPosition(translation);
	_pipeline.SetRotation(rotation);
	_pipeline.SetScale(scale);
	GLuint VBO;
	GLuint IBO;
	drawMe.GetBuffers(VBO, IBO);
	_pipeline.Draw(VBO, IBO);

	//pass the draw call to the next node
	//passing along the transforms
	std::list<Node>::iterator iter;
	for (iter = _children.begin(); iter != _children.end(); ++iter) {
		(*iter).Draw(_pipeline.GetTransform());
	}
}
