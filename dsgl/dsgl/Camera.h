#pragma once
#include "math_3d.h"
#include "Node.h"
#include "SceneGraph.h"
class Camera : public Component
{
public:
	Camera(PersProjInfo& info);
	~Camera();
	void Update();
	void Draw(Node world);

private:
	Matrix4f m_perspective;
};


