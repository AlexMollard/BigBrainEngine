#pragma once
#include "ShaderManager.h"

class Camera
{
public:
	Camera();
	~Camera();

	glm::mat4 Projection;
	glm::mat4 View;

	void Update(float deltaTime, GLFWwindow *window);
	void processInput(GLFWwindow *window);
	const GLFWvidmode* windowMode;
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	glm::vec3 cameraPos = glm::vec3(0.0f, 1.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	double mouseX;
	double mouseY;
	double lastX;
	double lastY;
	float yaw;
	float pitch;
	bool firstMouse = true;
	float cameraSpeed = 0.05f;
	int windowWidth;
	int windowHeight;
};

