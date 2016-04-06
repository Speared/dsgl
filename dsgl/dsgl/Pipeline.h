#pragma once
#include "math_3d.h"
#include <gl\glew.h>
#include <gl\glut.h>
class Pipeline
{
public:
	//TODO: handle the pipeline owning shaders far better
	//assuming I even want to keep this here
	//for now it's just hardcoded
	const char* shaderName = "translation shader";
	const char* uniformName = "gWorld";

	Pipeline();
	Pipeline(Vector3f scale, Vector3f position, Vector3f rotation);
	~Pipeline();
	void SetScale(Vector3f scale);
	void SetPosition(Vector3f position);
	void SetRotation(Vector3f rotation);
	void SetParentTrans(Matrix4f parentTrans);
	void Draw(GLuint &VBO, GLuint &IBO);
	Matrix4f GetTransform();
private:
	Matrix4f m_transformation;
	Matrix4f m_scale_trans, m_rotate_trans, m_position_trans;
	Matrix4f m_parent_trans;
	//set to true whenever values are changed
	bool dirty;

	void CalculateTransform();
};


