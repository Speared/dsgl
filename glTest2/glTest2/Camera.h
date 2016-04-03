#pragma once
#include "math_3d.h"
#include "Node.h"
class Camera
{
public:
	Camera(PersProjInfo& info, Vector3f& target, Vector3f& up);
	~Camera();
	void Draw(Node world);
	
private:
	//void SetPerspectiveMatrix(PersProjInfo& info);
	Matrix4f m_perspective;
	Matrix4f m_camera_trans;
};


