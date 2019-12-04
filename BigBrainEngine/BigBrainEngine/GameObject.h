#pragma once
#include "ModelManager.h"
class GameObject
{
public:
	GameObject(Camera* cam, glm::vec3 posititon, glm::vec3 color = glm::vec3(1, 1, 1));
	~GameObject();

	ModelManager* modelManager;

	glm::vec3 Posititon = glm::vec3(0.0f);

	void Update(float deltaTime);
	void Draw(float deltaTime);
	float fTime = 0.0f;

	void setPosition(glm::vec3 newPos, float delta);
	glm::vec3 getPosition();
	glm::vec3 ObjectColour;
};
