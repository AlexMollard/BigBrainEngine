#include <stdio.h>
#include <GL/glew.h>
#include <iostream>
#include "window.h"

void EngineLoop(float delta)
{
	// Clear the window
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

}

int main(int argc)
{
	// Creating a window
	if (!Window_intit(1920,1080, (char*)"Big Brain"))
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

	// Triangle positions (Vertices)
	static const GLfloat trainglePositions[6]
	{
		-0.5f, -0.5f,
		 0.0f,  0.5f,
		 0.5f, -0.5f
	};

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), trainglePositions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	// If the window is not closed enable the engine loop
	while (!Window_shouldClose())
	{
		Window_update(EngineLoop);

		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	// Destroy the window and free memory
	Window_destroy();

	return 0;
}
