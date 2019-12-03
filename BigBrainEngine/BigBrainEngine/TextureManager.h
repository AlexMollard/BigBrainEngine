#pragma once
#include "ShaderManager.h"
class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	GLuint loadBMP_custom(const char* imagepath);

	// Image Read vars
	GLuint image;

	// Data read from the header of the BMP file
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     // Position in the file where the actual data begins
	unsigned int width, height;
	unsigned int imageSize;   // = width*height*3

	// Actual RGB data
	unsigned char* data;

	GLuint texBuffer;
};
