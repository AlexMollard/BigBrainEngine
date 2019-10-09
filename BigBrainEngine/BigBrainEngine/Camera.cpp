#include "Camera.h"

Camera::Camera()
{
	windowMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	windowWidth = windowMode->width;
	windowHeight = windowMode->height;

	Projection = glm::perspective((float)glm::radians(45.0f), (float)windowWidth / (float)windowWidth, 0.1f, 100.0f);
	View = glm::lookAt(glm::vec3(1, 1, 4), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
}


Camera::~Camera()
{
}
