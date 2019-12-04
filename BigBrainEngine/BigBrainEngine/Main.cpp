#include <chrono>
#include <thread>
#include "window.h"
#include "Shapes.h"
#include "Camera.h"
#include "GameObject.h"
#include <time.h>
#include <crtdbg.h>
#include <stdio.h>
#define xRES 700
#define yRES 700
bool WindowClose = false;
double previousTime = 0;
int frameCount = 0;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		// Destroy the window and free memory
		WindowClose = true;
	}
}

void GetFPS()
{
	double currentTime = glfwGetTime();
	frameCount++;
	if (currentTime - previousTime >= 1.0)
	{
		// Display the frame count here any way you want.
		std::cout << frameCount << std::endl;

		frameCount = 0;
		previousTime = currentTime;
	}
}

int main(int argc)
{
	//At start of main()
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Creating a window
	if (!Window_intit(xRES, yRES, (char*)"Big Brain"))
	{
		std::cout << "Failed to load window" << std::endl;
		return 1;
	}

	// Initializing Glew
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Glew is not havig a good time" << std::endl;
	}

	// Outputting OpenGL Version and build
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	// Get user input
	glfwSetKeyCallback(Window, key_callback);

	const int cubeAmount = 1;

	Camera* camera = new Camera(Window);
	GameObject* cube = new GameObject(camera, glm::vec3(0, 1, 0));;

	// If the window is not closed enable the engine loop
	while (!Window_shouldClose() && !WindowClose)
	{
		GetFPS();

		Window_update();
		camera->Update(delta, Window);

		cube->Update(delta);
	}

	// Destroy the window and free memory
	Window_destroy();

	delete cube;
	delete camera;

	return 0;
}
