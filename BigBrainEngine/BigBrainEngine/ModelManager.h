#pragma once
#include "MaterialManager.h"
#include "VertexManager.h"
#include "Camera.h"
class ModelManager
{
public:
	ModelManager(Camera* cam);
	~ModelManager();

	void Update(float deltaTime);

	Camera* camera;
	MaterialManager* materialManager;
	VertexManager* vertexManager;
	GLuint MatrixID;

	float tempValue;

	glm::mat4 mvp;
	glm::mat4 Model;
};

