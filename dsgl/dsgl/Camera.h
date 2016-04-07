#pragma once
#include <list>
#include "math_3d.h"
#include "Node.h"
#include "SceneGraph.h"
class Camera : public Component
{
public:
	static std::list<Camera*> ActiveCameras;
	static void DrawAllCameras(Node node);
	static void DrawAllCameras();
	Camera(PersProjInfo& info);
	~Camera();
	void Update();
	void Draw(Node world);

private:
	Matrix4f m_perspective;
};


