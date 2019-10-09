#include "GameObject.h"



GameObject::GameObject(Camera* cam, glm::vec3 posititon)
{
	Posititon = posititon;
	modelManager = new ModelManager(cam);
	modelManager->Model = glm::translate(modelManager->Model, Posititon);
}

GameObject::~GameObject()
{
	delete modelManager;
}

void GameObject::Update(float deltaTime)
{
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
	//modelManager->Model = glm::translate(modelManager->Model, Posititon);
}

glm::vec3 GameObject::getPosition()
{
	return Posititon;
}
