#include <stdlib.h>
#include <GLFW/glfw3.h>

// Main Window
GLFWwindow *Window;

// DeltaTime
double last = 0.0;
double now = 0.0;
float delta = 1.0f;

// Window Functions
int Window_intit(int width, int height, char* name);
void Window_update(void (*update)(float));
int Window_shouldClose();
void Window_destroy();

int Window_intit(int width, int height, char* name)
{
	if (!glfwInit())
	{
		return -1;
	}

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	Window = glfwCreateWindow(width, height, name, NULL, NULL);

	if (!Window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(Window);

	return 1;

}

void Window_update(void(*update)(float))
{
	last = glfwGetTime();

	// Clear the window

	(*update)(delta);






	glfwSwapBuffers(Window);
	glfwPollEvents();

	glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	now = glfwGetTime();
	delta = (float)(now - last) * 10.0f;
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