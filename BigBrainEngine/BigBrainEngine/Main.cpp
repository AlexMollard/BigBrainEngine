#include <stdio.h>
#include <GL/glew.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "window.h"
#include "BigBrainMath.h"


static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const GLchar* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id,GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* errorMessage = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, errorMessage);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "Vertex" : "fragment") << "Shader" << std::endl;
		std::cout << errorMessage << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	int Success;
	glGetProgramiv(program, GL_LINK_STATUS, &Success);
	if (Success == GL_FALSE) 
	{
		char errorMessage[128];
		int errorSize;
		glGetProgramInfoLog(program, 128, &errorSize, errorMessage);
		std::cout << "Error linking shader program:" << std::endl;
		std::cout << errorMessage << std::endl;
	}


	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void EngineLoop(float delta)
{


}


GLfloat * Hex_Corner(int i, float trisize)
{
	float angle_deg = 60 * i;
	float angle_rad =  M_PI / 180 * angle_deg;

	GLfloat Point[2] = { (trisize * cos(angle_rad)), (trisize * sin(angle_rad))};

	return Point;
}

int main(int argc)
{
	// Creating a window
	if (!Window_intit(960, 720, (char*)"Big Brain"))
	{
		std::cout << "Failed to load window" << std::endl;
		return 1;
	}

	// Initializing Glew
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Glew is not havig a bad time" << std::endl;
	}

	// Outputting OpenGL Version and build
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	int TriTotal = 0;
	float triSize = 0.5f;

	std::vector<GLfloat>triangles;

	for (int i = 0; i < 1; i++)
	{
		TriTotal++;

		GLfloat* currentCorner = Hex_Corner(i, triSize);	// [0] = x, [1] = y

		currentCorner[0] = (currentCorner[0] * 0.5f + 0.5f);
		currentCorner[1] = (currentCorner[1] * 0.5f + 0.5f);

		// Left
		triangles.push_back(-0.5f);  triangles.push_back(-0.5f);  triangles.push_back(0.0f);
		
		// Right
		triangles.push_back(0.5f); triangles.push_back(0.5f); triangles.push_back(0.0f);
		
		// Center
		triangles.push_back(0); triangles.push_back(currentCorner[1]); triangles.push_back(0.0f);
	}

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 9 * TriTotal, triangles.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


	std::string vertexShader =
		"#version 330 core\n"
		"\n"
		"layout(location = 0) in vec4 Position; \n"
		"\n"
		"void main()\n"
		"{\n"
		"	gl_Position = Position;\n"
		"}\n"
		;


	std::string fragmentShader =
		"#version 330 core\n"
		"\n"
		"out vec4 FragColor; \n"
		"uniform vec3 triColour;"
		"\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(triColour,1.0);\n"
		"}\n"
		;


	GLuint shader = CreateShader(vertexShader, fragmentShader);

	GLuint colourID = glGetUniformLocation(shader, "triColour");


	glUseProgram(shader);
	glUniform3f(colourID, 1.0f, 0.5f, 0.0f);

	int frameCount = 0;

	// If the window is not closed enable the engine loop
	while (!Window_shouldClose())
	{
		frameCount++;
		Window_update(EngineLoop);

		//float value = sin(frameCount * 0.01f) * 0.5f + 0.5f;
		
		glUniform3f(colourID, 1.0f, 1.0f, 0.0f);

		glDrawArrays(GL_TRIANGLES, 0, 3 * TriTotal);
		
	}

	glDeleteProgram(shader);

	// Destroy the window and free memory
	Window_destroy();

	return 0;
}
