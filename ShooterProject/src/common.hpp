#pragma once

// stdlib
#include <iostream>

// GLFW
#define GLFW_DLL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// glm
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

extern char* WindowTitle;
extern int WindowWidth;
extern int WindowHeight;

struct Mesh
{
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
};

struct ColorVertex
{
	glm::vec3 pos;
	glm::vec4 color;
};

struct TextureVertex
{
	glm::vec3 pos;
	glm::vec2 texPos;
};
