#pragma once
#include "Shapes.h"
class VertexManager
{
public:
	VertexManager();
	~VertexManager();

	void Update();

	unsigned int vBuffer;
	unsigned int iBuffer;
	Cube3D newCube;
};

