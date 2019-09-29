#include <stdio.h>
#include <GL/glew.h>
#include <iostream>

#include "window.h"

void GameLoop(float delta)
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc)
{

	if (!Window_intit(1920,1080, (char*)"Big Brain"))
	{
		std::cout << "Failed to load window" << std::endl;
		return 1;
	}

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Glew is not okay" << std::endl;
	}

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	while (!Window_shouldClose())
	{
		Window_update(GameLoop);
	}


	Window_destroy();
	return 0;
}
