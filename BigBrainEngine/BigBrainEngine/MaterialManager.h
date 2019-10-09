#pragma once
#include "ShaderManager.h"
#include "ColourManager.h"
class MaterialManager
{
public:
	MaterialManager(std::string shaderDIR, int colorBufferSize);
	~MaterialManager();

	void Update(float deltaTime);

	Colour* colorManager;
	ShaderManager* shaderManager;

	GLuint colorBuffer;
	GLuint shaderProgram;
	GLuint vertexAttribute;

	const GLFWvidmode* windowMode;

	int windowWidth;
	int windowHeight;

	float updateTimer = 0.0f;

	//Uniforms
	GLuint iResolution;
	GLuint iTime;
};

