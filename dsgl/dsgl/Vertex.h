#pragma once
#include "math_3d.h"
struct Vertex
{
	Vector3f position;
	Vector2f textureCoordinate;
	Vertex(Vector3f position, Vector2f textureCoordinate) :
		position(position), textureCoordinate(textureCoordinate) {}
};