#include "ModelManager.h"

ModelManager::ModelManager(Camera* cam, glm::vec3 colorData)
{
	camera = cam;
	materialManager = new MaterialManager("BasicTwo.Shader", 12 * 3 * 3, colorData);

	vertexManager = new VertexManager();
	textureManager = new TextureManager();

	Model = glm::mat4(1.0f);

	MatrixID = glGetUniformLocation(materialManager->shaderProgram, "MVP");

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
	tempValue = 0.0f;
}

ModelManager::~ModelManager()
{
	delete materialManager;
	delete vertexManager;
	delete textureManager;
}

void ModelManager::Draw(float deltaTime)
{
	//tempValue = deltaTime / 10;
	//Model = glm::rotate(Model,tempValue, glm::vec3(1));

	materialManager->Update(deltaTime);
	vertexManager->Update();

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
	mvp = camera->Projection * camera->View * Model;
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
}