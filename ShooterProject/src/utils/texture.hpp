#pragma once

// stdlib
#include <iostream>
#include <fstream>

// GLFW
#define GLFW_DLL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Texture
{
public:
	Texture();
	~Texture();

	bool init(const char* image);
	
	GLuint id;
	int width;
	int height;
};
