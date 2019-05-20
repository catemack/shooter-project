#pragma once

// stdlib
#include <string>
#include <fstream>
#include <sstream>

// glfw
#define GLFW_DLL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Effect
{
public:
	Effect();
	~Effect();

	bool init(const char* vsPath, const char* fsPath);

	GLuint program;

private:
	GLuint vertex;
	GLuint fragment;
};
