#include <GL/glew.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "window.h"
#include "BigBrainMath.h"

struct ShaderPROSource
{
	std::string VertexSource;
	std::string FragmentSource;
};


static ShaderPROSource ParseShader(const std::string& filePath)
{
	std::ifstream stream(filePath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::stringstream ss[2];
	std::string line;
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}

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
	// Shader Uniforms
	static float Scale = 0.75f;

	// Circle Attributes
	int TriTotal = 0;
	int faces = 200;
	float triangleBufferCount = 0.0f;
	float triSize = 360 / faces;
	float radiansSize = triSize * M_PI / 180;
	int fullCircle = (360 / triSize);

	// Triangle buffer
	std::vector<GLfloat>triangles;

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

	// Get user input
	glfwSetKeyCallback(Window, key_callback);

	// Get shder source
	ShaderPROSource source = ParseShader("Basic.shader");

	// Create shader program
	GLuint shader = CreateShader(source.VertexSource, source.FragmentSource);

	// Assign shader uniform variables
	GLuint colourID = glGetUniformLocation(shader, "triColour");
	GLuint gScaleLocation = glGetUniformLocation(shader, "gScale");

	// Use this shader
	glUseProgram(shader);

	// If the window is not closed enable the engine loop
	while (!Window_shouldClose())
	{
		Window_update(EngineLoop);
		
		if (TriTotal < fullCircle * 2)
		{
			triangleBufferCount += radiansSize;
			TriTotal ++;
			triangles.push_back(cos(triangleBufferCount)); triangles.push_back(sin(triangleBufferCount) ); triangles.push_back(0.0f);
			triangles.push_back(cos(triangleBufferCount - radiansSize)); triangles.push_back(sin(triangleBufferCount - radiansSize)); triangles.push_back(0.0f);
			triangles.push_back(cos(triangleBufferCount - (radiansSize / 2)) / 2); triangles.push_back(sin(triangleBufferCount - (radiansSize / 2)) / 2); triangles.push_back(0.0f);
			
			TriTotal++;
			triangles.push_back(cos(triangleBufferCount - (radiansSize / 2)) / 2); triangles.push_back(sin(triangleBufferCount - (radiansSize / 2)) / 2); triangles.push_back(0.0f);
			triangles.push_back(cos(triangleBufferCount + (radiansSize / 2)) / 2); triangles.push_back(sin(triangleBufferCount + (radiansSize / 2)) / 2); triangles.push_back(0.0f);
			triangles.push_back(cos(triangleBufferCount)); triangles.push_back(sin(triangleBufferCount)); triangles.push_back(0.0f);

			//	Triangles
			GLuint buffer;
			glGenBuffers(1, &buffer);
			glBindBuffer(GL_ARRAY_BUFFER, buffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 9 * TriTotal, triangles.data(), GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		}
		else
			Scale -= 0.0001f;

		// Change colour
		glUniform3f(colourID, 1.0f, 1.0f, 0.0f);

		// Change scale
		glUniform1f(gScaleLocation, Scale);
		
		// Draw all tris
		glDrawArrays(GL_TRIANGLES, 0, 3 * TriTotal);
	}

	glDeleteProgram(shader);

	// Destroy the window and free memory
	Window_destroy();

	return 0;
}
