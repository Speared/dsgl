#pragma once
#include "math_3d.h"

class Pipeline
{
public:
	Pipeline();
	Pipeline(Vector3f scale, Vector3f position, Vector3f rotation);
	~Pipeline();
	void SetScale(Vector3f scale);
	void SetPosition(Vector3f position);
	void SetRotation(Vector3f rotation);
	Matrix4f GetTransform();
private:
	Matrix4f m_transformation;
	Matrix4f m_scale_trans, m_rotate_trans, m_position_trans;
	//set to true whenever values are changed
	bool dirty;
};


