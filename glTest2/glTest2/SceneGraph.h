#pragma once
#include "Node.h"
#include "math_3d.h"
struct SceneGraph {
	static Node root;
	static void Init() {
		root.translation = Vector3f(0.0f);
		root.rotation = Vector3f(0.0f);
		root.scale = Vector3f(1.0f);
	}
};

