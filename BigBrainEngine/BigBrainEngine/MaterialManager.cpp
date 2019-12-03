#include "MaterialManager.h"

MaterialManager::MaterialManager(std::string shaderDIR, int colorBufferSize, glm::vec3 colour)
{
	shaderManager = new ShaderManager(shaderDIR);
	shaderProgram = shaderManager->shader;

	colorManager = new Colour(colorBufferSize, colour);
	colorBuffer = colorManager->colorbuffer;

	windowMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	windowWidth = windowMode->width;
	windowHeight = windowMode->height;

	vertexAttribute = GL_VERTEX_ARRAY;

	// Uniforms
	iResolution = glGetUniformLocation(shaderProgram, "iResolution");
	iTime = glGetUniformLocation(shaderProgram, "iTime");
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
	updateTimer += deltaTime;

	glUseProgram(shaderProgram);

	// Binding color buffer
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);

	glEnableVertexAttribArray(1);

	glEnableVertexAttribArray(vertexAttribute);
	glVertexAttribPointer(vertexAttribute, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Change uniforms
	glUniform2f(iResolution, windowWidth, windowHeight);
	glUniform1f(iTime, updateTimer);
}