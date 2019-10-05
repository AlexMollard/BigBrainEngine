#include <stdio.h>
#include <GL/glew.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <chrono> // std::chrono::microseconds
#include <thread> // std::this_thread::sleep_for

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

float Clamp(float input, float high, float low)
{
	if (input <= high || input >= low)
		return input;

	return (input > high ? high : low);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		// Destroy the window and free memory
		Window_destroy();

		exit(0);
	}
}

int main(int argc)
{
	// Creating a window
	if (!Window_intit(1920, 1080, (char*)"Big Brain"))
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



	glfwSetKeyCallback(Window, key_callback);


	std::string vertexShader =
		"#version 330 core\n"
		"\n"
		"layout(location = 0) in vec4 Position; \n"
		"uniform float gScale;"
		"\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(gScale * Position.x, gScale * Position.y, Position.z, 1.0);\n"
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

	static float Scale = 0.75f;

	GLuint shader = CreateShader(vertexShader, fragmentShader);

	GLuint colourID = glGetUniformLocation(shader, "triColour");

	GLuint gScaleLocation = glGetUniformLocation(shader, "gScale");

	glUseProgram(shader);

	float frameCount = 0.0f;

	int TriTotal = 0;

	std::vector<GLfloat>triangles;

	// Must be below 180
	float triSize = 5.625f;

	float radiansSize = triSize * M_PI / 180;
	int fullCircle = (360 / triSize);

	// If the window is not closed enable the engine loop
	while (!Window_shouldClose())
	{
		frameCount += radiansSize;
		Window_update(EngineLoop);
		Scale += 0.0001f;

		//float value = sin(frameCount * 0.01f) * 0.5f + 0.5f;
		
		if (TriTotal < fullCircle * 2)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds{100});

			TriTotal ++;

			// Top
			triangles.push_back(cos(frameCount)); triangles.push_back(sin(frameCount) ); triangles.push_back(0.0f);
			
			
			// Right
			triangles.push_back(cos(frameCount - radiansSize)); triangles.push_back(sin(frameCount - radiansSize)); triangles.push_back(0.0f);
			
			
			// Left
			triangles.push_back(cos(frameCount - (radiansSize / 2)) / 2); triangles.push_back(sin(frameCount - (radiansSize / 2)) / 2); triangles.push_back(0.0f);
			
			
			TriTotal++;
			// Top
			triangles.push_back(cos(frameCount - (radiansSize / 2)) / 2); triangles.push_back(sin(frameCount - (radiansSize / 2)) / 2); triangles.push_back(0.0f);


			// Right
			triangles.push_back(cos(frameCount + (radiansSize / 2)) / 2); triangles.push_back(sin(frameCount + (radiansSize / 2)) / 2); triangles.push_back(0.0f);


			// Left
			triangles.push_back(cos(frameCount)); triangles.push_back(sin(frameCount)); triangles.push_back(0.0f);




			//	Triangles

			GLuint buffer;
			glGenBuffers(1, &buffer);
			glBindBuffer(GL_ARRAY_BUFFER, buffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 9 * TriTotal, triangles.data(), GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		}

		glUniform3f(colourID, 1.0f, 1.0f, 0.0f);
		glUniform1f(gScaleLocation, Scale);
		
		glDrawArrays(GL_TRIANGLES, 0, 3 * TriTotal);
		
	}

	glDeleteProgram(shader);

	// Destroy the window and free memory
	Window_destroy();

	return 0;
}
