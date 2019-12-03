#include "GameObject.h"

GameObject::GameObject(Camera* cam, glm::vec3 posititon, glm::vec3 Color)
{
	Posititon = posititon;
	ObjectColour = Color;
	modelManager = new ModelManager(cam, ObjectColour);

	modelManager->Model = glm::translate(modelManager->Model, Posititon);
	fTime = Posititon.x / 4.0f + Posititon.y / 4.0f;
}

GameObject::~GameObject()
{
	delete modelManager;
}

void GameObject::Update(float deltaTime)
{
	fTime += deltaTime * 1.0f;
	setPosition(glm::vec3(Posititon.x, Posititon.y, Posititon.z));
	Draw(deltaTime);
}

void GameObject::Draw(float deltaTime)
{
	modelManager->Draw(deltaTime);
}

void GameObject::setPosition(glm::vec3 newPos)
{
	Posititon = newPos;
	modelManager->Model[3][0] = newPos[0];
	modelManager->Model[3][1] = newPos[1];
	modelManager->Model[3][2] = newPos[2];
}

glm::vec3 GameObject::getPosition()
{
	return Posititon;
}