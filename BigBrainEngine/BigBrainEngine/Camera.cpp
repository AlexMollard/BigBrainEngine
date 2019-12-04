#include "Camera.h"
int width, height;
glm::mat4 newProjection;
void window_size_callback(GLFWwindow* window, int width, int height)
{
	glfwGetWindowSize(window, &width, &height);
	newProjection = glm::perspective((float)glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
	glViewport(0, 0, width, height);
}

Camera::Camera(GLFWwindow* window)
{
	windowMode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	Projection = glm::perspective((float)glm::radians(45.0f), 0.0f, 0.1f, 100.0f);
	View = glm::lookAt(glm::vec3(1, 2, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	glfwSetWindowSizeCallback(window, window_size_callback);
	window_size_callback(window, (float)windowWidth, (float)windowWidth);
}

Camera::~Camera()
{
}

void Camera::Update(float deltaTime, GLFWwindow *window)
{
	//processInput(window, deltaTime);

	Projection = newProjection;

	View = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::processInput(GLFWwindow *window, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		cameraSpeed = deltaTime * 4.0f;
	else
		cameraSpeed = deltaTime * 2.0f;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

	glfwGetCursorPos(window, &mouseX, &mouseY);
	mouse_callback(window, mouseX, mouseY);
}

void Camera::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.05;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}