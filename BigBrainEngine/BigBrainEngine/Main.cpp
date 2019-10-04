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

	int TriTotal = 0;

	std::vector<GLfloat>triangles;

	//for (int i = 1; i < 4; i++)
	//{
	//	TriTotal++;

	//	// Top
	//	triangles.push_back(cos(i) / 2); triangles.push_back(sin(i) / 2); triangles.push_back(0.0f);


	//	// Right
	//	triangles.push_back(cos(i - 1) / 2); triangles.push_back(sin(i - 1) / 2); triangles.push_back(0.0f);

	//	
	//	// Left
	//	triangles.push_back(cos(i) / 4); triangles.push_back(sin(i) / 4); triangles.push_back(0.0f);

	//}



	////	Triangles
	//
	//GLuint buffer;
	//glGenBuffers(1, &buffer);
	//glBindBuffer(GL_ARRAY_BUFFER, buffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 9 * TriTotal, triangles.data(), GL_STATIC_DRAW);
	//
	//glEnableVertexAttribArray(0);
	//
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//int DotTotal = 0;
	//std::vector<GLfloat>dots;
	//
	//for (int i = 0; i < 400; i++)
	//{
	//	DotTotal++;
	//
	//	// Dot
	//	dots.push_back(cos(i) / 2); dots.push_back(sin(i) / 2); dots.push_back(0.0f);
	//
	//	DotTotal++;
	//	dots.push_back(cos(i) / 4); dots.push_back(sin(i) / 4); dots.push_back(0.0f);
	//}
	//
	//GLuint VBO;
	//glGenBuffers(1, &VBO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * DotTotal, dots.data(), GL_STATIC_DRAW);
	//
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//glPointSize(10.0f);

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

	float frameCount = 0.0f;

	// Must be below 180
	float triSize = 5.625f;

	float radiansSize = triSize * M_PI / 180;
	int fullCircle = (360 / triSize);

	// If the window is not closed enable the engine loop
	while (!Window_shouldClose())
	{
		frameCount += radiansSize;
		Window_update(EngineLoop);

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

		// Draw Dots
		//glDrawArrays(GL_POINTS, 0, 1 * DotTotal);
		
		glDrawArrays(GL_TRIANGLES, 0, 3 * TriTotal);
		
	}

	glDeleteProgram(shader);

	// Destroy the window and free memory
	Window_destroy();

	return 0;
}
