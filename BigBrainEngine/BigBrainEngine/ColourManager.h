#pragma once
#include "ShaderManager.h"
class Colour
{
public:
	Colour(int BufferSize, glm::vec3 colourData);
	~Colour();

	//12 * 3 * 3
	std::vector<GLfloat> colorBufferData;

	GLuint colorbuffer;
};
