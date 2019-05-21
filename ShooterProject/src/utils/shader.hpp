#pragma once

// stdlib
#include <string>
#include <fstream>
#include <sstream>

// glfw
#define GLFW_DLL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader
{
public:
	Shader();
	~Shader();

	bool init(const char* vsPath, const char* fsPath);
	void use();

	GLuint program;

private:
	GLuint vertex;
	GLuint fragment;
};
