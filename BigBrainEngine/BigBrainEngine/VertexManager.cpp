#include "VertexManager.h"
#include "ShaderManager.h"

VertexManager::VertexManager()
{
	glGenBuffers(1, &vBuffer); // Vertex buffer
	glGenBuffers(1, &iBuffer); // indices buffer

	size_t vSize = sizeof(newCube.vertices);

	glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
	glBufferData(GL_ARRAY_BUFFER, vSize, 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vSize, newCube.vertices);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(newCube.indices), newCube.indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// bind VBOs before drawing - unique per model, would to happen every frame
	glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBuffer);

	// enable vertex arrays
	glEnableClientState(GL_VERTEX_ARRAY);

	// specify vertex arrays with their offsets
	glVertexPointer(3, GL_FLOAT, 0, nullptr);
}

VertexManager::~VertexManager()
{
	// disable vertex arrays
	glDisableClientState(GL_VERTEX_ARRAY);

	// unbind VBOs
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void VertexManager::Update()
{
	// Only needs to happen if model changes

	//glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBuffer);
	//
	// enable vertex arrays
	//glEnableClientState(GL_VERTEX_ARRAY);

	// specify vertex arrays with their offsets
	//glVertexPointer(3, GL_FLOAT, 0, nullptr);
}