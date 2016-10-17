#include "Camera.h"
std::list<Camera*> Camera::ActiveCameras;
Camera *Camera::currentlyDrawingCamera;

void Camera::DrawAllCameras(Node node) {
	std::list<Camera*>::iterator iter = ActiveCameras.begin();
	for (; iter != ActiveCameras.end(); iter++) {
		//keep track of which camera is drawing this scene 
		currentlyDrawingCamera = (*iter);
		(*iter)->Draw(node);
	}
	//when we're done drawing make a note that there is no current camera anymore
	currentlyDrawingCamera = 0;
}

void Camera::DrawAllCameras() {
	DrawAllCameras(SceneGraph::root);
}

Camera::Camera(PersProjInfo& info)
{
	m_perspective.InitPersProjTransform(info);
	ActiveCameras.push_front(this);
}

Camera::~Camera()
{
	ActiveCameras.remove(this);
}

void Camera::Update() 
{
	//Draw(SceneGraph::root);
}

void Camera::Draw(Node world)
{

	//draws the given node with our perspective and the inverse of our transform as the parent transform
	Matrix4f myTrans = myNode->GetTransform();
	world.Draw(m_perspective * myTrans.Inverse());

}
