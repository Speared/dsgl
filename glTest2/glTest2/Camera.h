#pragma once
#include "math_3d.h"
#include "Node.h"
class Camera
{
public:
	Camera(PersProjInfo& info);
	~Camera();
	void Draw(Node world);

private:
	void SetPerspectiveMatrix(PersProjInfo& info);
	Matrix4f m_perspective;
};


