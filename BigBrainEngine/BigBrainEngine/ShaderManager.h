#pragma once
#include "Shapes.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

struct ShaderPROSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();

	ShaderPROSource ParseShader(const std::string& filePath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
};


