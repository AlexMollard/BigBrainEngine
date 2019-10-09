#include <chrono>
#include <thread>
#include "window.h"
#include "Shapes.h"
#include "Camera.h"
#include "GameObject.h"
#include <crtdbg.h>
#define xRES 720
#define yRES 480
bool WindowClose = false;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		// Destroy the window and free memory
		WindowClose = true;
	}
}

int main(int argc)
{
	//At start of main()
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	srand(time(NULL));

	// Creating a window
	if (!Window_intit(xRES, yRES, (char*)"Big Brain"))
	{
		std::cout << "Failed to load window" << std::endl;
		return 1;
	}

	// Initializing Glew
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Glew is not havig a bad time" << std::endl;
	}

	// Outputting OpenGL Version and build
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	Camera* camera = new Camera();
	GameObject* cube = new GameObject(camera, glm::vec3(0,0,0));

	// Get user input
	glfwSetKeyCallback(Window, key_callback);

	// Allow GPU to not draw vert over other verts
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);


	// If the window is not closed enable the engine loop
	while (!Window_shouldClose() && !WindowClose)
	{
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
