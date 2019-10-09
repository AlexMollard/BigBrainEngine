#include "Camera.h"

Camera::Camera()
{
	windowMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	windowWidth = windowMode->width;
	windowHeight = windowMode->height;

	Projection = glm::perspective((float)glm::radians(45.0f), (float)windowWidth / (float)windowWidth, 0.1f, 100.0f);
	View = glm::lookAt(glm::vec3(1, 2, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
}


Camera::~Camera()
{
}

void Camera::Update(float deltaTime, GLFWwindow *window)
{
	processInput(window);
	View = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::processInput(GLFWwindow *window)
{
		float cameraSpeed = 0.05f; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}