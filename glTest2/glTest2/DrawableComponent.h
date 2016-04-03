#pragma once
#include "Component.h"
#include "math_3d.h"
class DrawableComponent : public Component
{
public:
	DrawableComponent();
	~DrawableComponent();
	//unlike update, any drawable objects need to know how to draw themself
	virtual void Draw(Matrix4f transform) = 0;
};

