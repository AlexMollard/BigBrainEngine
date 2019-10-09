#pragma once
#include "ShaderManager.h"

class Camera
{
public:
	Camera();
	~Camera();

	glm::mat4 Projection;
	glm::mat4 View;

	const GLFWvidmode* windowMode;

	int windowWidth;
	int windowHeight;
};

