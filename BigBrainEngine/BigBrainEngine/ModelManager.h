#pragma once
#include "MaterialManager.h"
#include "VertexManager.h"
#include "TextureManager.h"
#include "Camera.h"
class ModelManager
{
public:
	ModelManager(Camera* cam, glm::vec3 colorData = glm::vec3(1, 1, 1));
	~ModelManager();

	void Draw(float deltaTime);

	Camera* camera;
	MaterialManager* materialManager;
	VertexManager* vertexManager;
	TextureManager* textureManager;
	GLuint MatrixID;

	float tempValue;

	glm::mat4 mvp;
	glm::mat4 Model;
};
