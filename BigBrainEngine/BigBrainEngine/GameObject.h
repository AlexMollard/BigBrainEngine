#pragma once
#include "ModelManager.h"
class GameObject
{
public:
	GameObject(Camera* cam, glm::vec3 posititon);
	~GameObject();

	ModelManager* modelManager;

	glm::vec3 Posititon = glm::vec3(0.0f);

	void Update(float deltaTime);
	void Draw(float deltaTime);

	void setPosition(glm::vec3 newPos);
	glm::vec3 getPosition();
};

