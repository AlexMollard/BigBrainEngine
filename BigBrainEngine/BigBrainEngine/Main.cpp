#include <stdio.h>
#include <GL/glew.h>
#include <iostream>
#include "window.h"

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
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
		char* errorMessage = (char*)alloca(Success * sizeof(char));
		glGetProgramInfoLog(program, Success, &Success, errorMessage);
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

	// Triangle positions (Vertices)
	static const GLfloat trainglePositions[9]
	{
		-0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f
	};

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 9, trainglePositions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


	std::string vertexShader =
		"#version 330 core\n"
		"\n"
		"layout(location = 0) in vec4 position; \n"
		"\n"
		"void main()\n"
		"{\n"
		"	gl_Position = position;\n"
		"}\n"
		;


	std::string fragmentShader =
		"#version 330 core\n"
		"\n"
		"layout(location = 0) out vec4 color; \n"
		"\n"
		"void main()\n"
		"{\n"
		"	color = vec4(1.0,1.0,0.0,1.0);\n"
		"}\n"
		;


	unsigned int shader = CreateShader(vertexShader, fragmentShader);
	glUseProgram(shader);

	// If the window is not closed enable the engine loop
	while (!Window_shouldClose())
	{
		Window_update(EngineLoop);

		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	glDeleteProgram(shader);

	// Destroy the window and free memory
	Window_destroy();

	return 0;
}
