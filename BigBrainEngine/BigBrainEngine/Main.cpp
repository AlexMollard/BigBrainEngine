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
		std::cout << "Glew is not havig a good time" << std::endl;
	}

	// Outputting OpenGL Version and build
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	const int cubeAmount = 1;

	Camera* camera = new Camera();
	GameObject* cube[cubeAmount][cubeAmount];
	float r = 404;

	srand(time(NULL));
	float RandomSeed = rand() % 100000;

	for (int x = 0; x < cubeAmount; x++)
	{
		for (int z = 0; z < cubeAmount; z++)
		{
			//float r = (double)rand() / (RAND_MAX + 1.0);
			//float g = (double)rand() / (RAND_MAX + 1.0);
			//float b = (double)rand() / (RAND_MAX + 1.0);
			r = (glm::simplex(glm::vec2(x * 0.1f + RandomSeed, z * 0.1f + RandomSeed)) * 0.5f) + 0.5f;

			cube[x][z] = new GameObject(camera, glm::vec3(x, 0, z));

			//if (r < 0.4f)
			//	cube[x][z] = new GameObject(camera, glm::vec3(x, 0.35f, z), glm::vec3(0.1f, 0.1f, r + 0.4f));
			//else if (r < 0.7f)
			//	cube[x][z] = new GameObject(camera, glm::vec3(x, r, z), glm::vec3(0.1f, r, 0.1f));
			//else
			//	cube[x][z] = new GameObject(camera, glm::vec3(x, r + 0.1f, z), glm::vec3(r - 0.4f, r - 0.4f, r - 0.4f));
		}
	}
	//Normalized Data
	//normalized = (x - min(x)) / (max(x) - min(x))

	// Get user input
	glfwSetKeyCallback(Window, key_callback);

	// Allow GPU to not draw vert over other verts
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	double previousTime = glfwGetTime();
	int frameCount = 0;

	// If the window is not closed enable the engine loop
	while (!Window_shouldClose() && !WindowClose)
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

		Window_update();
		camera->Update(delta, Window);

		// Update Cubes
		for (int i = 0; i < cubeAmount; i++)
		{
			for (int z = 0; z < cubeAmount; z++)
			{
				cube[i][z]->Update(delta);
			}
		}
	}

	// Destroy the window and free memory
	Window_destroy();

	for (int i = 0; i < cubeAmount; i++)
	{
		for (int z = 0; z < cubeAmount; z++)
		{
			delete cube[i][z];
		}
	}
	delete camera;

	return 0;
}