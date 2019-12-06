#include "MaterialManager.h"

MaterialManager::MaterialManager(std::string shaderDIR, int colorBufferSize, glm::vec3 colour)
{
	//vertexColour = colour;

	shaderManager = new ShaderManager(shaderDIR);
	shaderProgram = shaderManager->shader;

	colorManager = new Colour(colorBufferSize, colour);
	colorBuffer = colorManager->colorbuffer;

	windowMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	windowWidth = windowMode->width;
	windowHeight = windowMode->height;

	// Uniforms
	iResolution = glGetUniformLocation(shaderProgram, "iResolution");
	iTime = glGetUniformLocation(shaderProgram, "iTime");
	colourUniform = glGetUniformLocation(shaderProgram, "MyColour");

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// Needs to happen if object uses diffrent shader
	glUseProgram(shaderProgram);
}

MaterialManager::~MaterialManager()
{
	// deactivate vertex attribs
	glDisableVertexAttribArray(vertexAttribute);

	delete shaderManager;
	delete colorManager;
}

void MaterialManager::Update(float deltaTime)
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	// Change uniforms
	glUniform2f(iResolution, windowWidth, windowHeight);
	glUniform1f(iTime, updateTimer);
	//glUniform3f(colourUniform, vertexColour.x, vertexColour.y, vertexColour.z);
}