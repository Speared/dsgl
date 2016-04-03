#include "Camera.h"

Camera::Camera(PersProjInfo& info)
{
	SetPerspectiveMatrix(info);
}

Camera::~Camera()
{
}

void Camera::Draw(Node world)
{
	//draws the given node with our perspective as the parent transform
	world.Draw(m_perspective);
	//world.Draw(Matrix4f::Identity());
}

//many thanks to Etay Meiri for the majority of this function
void Camera::SetPerspectiveMatrix(PersProjInfo& info)
{
	const float ar = info.Width / info.Height;
	const float zNear = info.zNear;
	const float zFar = info.zFar;
	const float zRange = zNear - zFar;
	const float tanHalfFOV = tanf(ToRadian(info.FOV / 2.0));

	m_perspective.m[0][0] = 1.0f / (tanHalfFOV * ar);
	m_perspective.m[0][1] = 0.0f;
	m_perspective.m[0][2] = 0.0f;
	m_perspective.m[0][3] = 0.0f;

	m_perspective.m[1][0] = 0.0f;
	m_perspective.m[1][1] = 1.0f / tanHalfFOV;
	m_perspective.m[1][2] = 0.0f;
	m_perspective.m[1][3] = 0.0f;

	m_perspective.m[2][0] = 0.0f;
	m_perspective.m[2][1] = 0.0f;
	m_perspective.m[2][2] = (-zNear - zFar) / zRange;
	m_perspective.m[2][3] = 2.0f * zFar * zNear / zRange;

	m_perspective.m[3][0] = 0.0f;
	m_perspective.m[3][1] = 0.0f;
	m_perspective.m[3][2] = 1.0f;
	m_perspective.m[3][3] = 0.0f;
}