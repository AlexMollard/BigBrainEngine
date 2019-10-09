#include "ColourManager.h"



Colour::Colour(int bufferSize)
{
	// Assign random colors for each vert
	for (int v = 0; v < 12 * 3; v++)
	{
		GLfloat u = (rand() % 10000) / 10000.0;
		round(u);
		colorBufferData.push_back(u);

		u = (rand() % 10000) / 10000.0;
		round(u);
		colorBufferData.push_back(u);

		u = (rand() % 10000) / 10000.0;
		round(u);
		colorBufferData.push_back(u);
	}

	//Set up for model, can go in model file
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, colorBufferData.size() * sizeof(GLfloat), colorBufferData.data(), GL_STATIC_DRAW);
}


Colour::~Colour()
{
}
