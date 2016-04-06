#include "Camera.h"

Camera::Camera(PersProjInfo& info)
{
	m_perspective.InitPersProjTransform(info);
}

Camera::~Camera()
{
}

void Camera::Update() 
{
	Matrix4f parentTrans = myNode->GetTransform();
	Draw(SceneGraph::root);
}

void Camera::Draw(Node world)
{
	//testing doing this closer to the way the tutorial wanted, to test these features of the node
	//Matrix4f rotationTrans;
	//rotationTrans.InitCameraTransform(myNode->forward, myNode->up);
	//Matrix4f positionTrans;
	//positionTrans.InitTranslationTransform(myNode->worldPos);
	//world.Draw(m_perspective * rotationTrans * positionTrans);

	//draws the given node with our perspective and the inverse of our transform as the parent transform
	Matrix4f myTrans = myNode->GetTransform();
	world.Draw(m_perspective * myTrans.Inverse());

}
