#include "Pipeline.h"
#include "ShaderManager.h"

Pipeline::Pipeline()
{
	SetScale(Vector3f());
	SetPosition(Vector3f());
	SetRotation(Vector3f());
}

Pipeline::Pipeline(Vector3f scale, Vector3f position, Vector3f rotation)
{
	SetScale(scale);
	SetPosition(position);
	SetRotation(rotation);
}

Pipeline::~Pipeline()
{
}

void Pipeline::SetScale(Vector3f scale)
{
	dirty = true;
	m_scale_trans.InitScaleTransform(scale);

}
void Pipeline::SetPosition(Vector3f position)
{
	dirty = true;
	m_position_trans.InitTranslationTransform(position);
}
void Pipeline::SetRotation(Vector3f rotation)
{
	dirty = true;
	m_rotate_trans.InitRotateTransform(rotation);
}
void Pipeline::SetParentTrans(Matrix4f parentTrans)
{
	dirty = true;
	m_parent_trans = parentTrans;
}

void Pipeline::CalculateTransform() {
	if (dirty) {
		dirty = false;
		m_transformation = m_parent_trans *  m_position_trans * m_rotate_trans * m_scale_trans;
	}
}

Matrix4f Pipeline::GetTransform()
{
	CalculateTransform();
	return m_transformation;
}