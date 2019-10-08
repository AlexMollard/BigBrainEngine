#ifndef MATH_HEADER
#define MATH_HEADER
#include "BigBrainMath.h"


struct Cube3D
{
	float vertices[72] =
	{
			 0.5f, 0.5f, 0.5f,  -0.5f, 0.5f, 0.5f,  -0.5f,-0.5f, 0.5f,  0.5f,-0.5f, 0.5f, // v0,v1,v2,v3 (front)
			 0.5f, 0.5f, 0.5f,   0.5f,-0.5f, 0.5f,   0.5f,-0.5f,-0.5f,  0.5f, 0.5f,-0.5f, // v0,v3,v4,v5 (right)
			 0.5f, 0.5f, 0.5f,   0.5f, 0.5f,-0.5f,  -0.5f, 0.5f,-0.5f, -0.5f, 0.5f, 0.5f, // v0,v5,v6,v1 (top)
			-0.5f, 0.5f, 0.5f,  -0.5f, 0.5f,-0.5f,  -0.5f,-0.5f,-0.5f, -0.5f,-0.5f, 0.5f, // v1,v6,v7,v2 (left)
			-0.5f,-0.5f,-0.5f,   0.5f,-0.5f,-0.5f,   0.5f,-0.5f, 0.5f, -0.5f,-0.5f, 0.5f, // v7,v4,v3,v2 (bottom)
			 0.5f,-0.5f,-0.5f,  -0.5f,-0.5f,-0.5f,  -0.5f, 0.5f,-0.5f,  0.5f, 0.5f,-0.5f  // v4,v7,v6,v5 (back)
	};

	unsigned int indices[36] =
	{
			0, 1, 2,   2, 3, 0,    // v0-v1-v2, v2-v3-v0 (front)
			4, 5, 6,   6, 7, 4,    // v0-v3-v4, v4-v5-v0 (right)
			8, 9,10,  10,11, 8,    // v0-v5-v6, v6-v1-v0 (top)
			12,13,14,  14,15,12,    // v1-v6-v7, v7-v2-v1 (left)
			16,17,18,  18,19,16,    // v7-v4-v3, v3-v2-v7 (bottom)
			20,21,22,  22,23,20     // v4-v7-v6, v6-v5-v4 (back)
	};

};

#endif