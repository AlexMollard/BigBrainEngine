#include <stdlib.h>
#include "ShaderManager.h"

// Main Window
GLFWwindow *Window;

// DeltaTime
double last = 0.0;
double now = 0.0;
float delta = 1.0f;

// Window Functions
int Window_intit(int width, int height, char* name);
void Window_update();
int Window_shouldClose();
void Window_destroy();

int Window_intit(int width, int height, char* name)
{
	if (!glfwInit())
	{
		return -1;
	}

	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	Window = glfwCreateWindow(width, height, name, NULL, NULL);
	glfwMakeContextCurrent(Window);
	glfwSwapInterval(2);
	if (!Window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(Window);

	// Allow GPU to not draw vert over other verts
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	return 1;
}

void Window_update()
{
	glfwSwapBuffers(Window);
	glfwPollEvents();

	glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	now = glfwGetTime();
	delta = (float)(now - last);
	last = now;
}

int Window_shouldClose()
{
	return glfwWindowShouldClose(Window);
}

void Window_destroy()
{
	glfwDestroyWindow(Window);
	glfwTerminate();
}