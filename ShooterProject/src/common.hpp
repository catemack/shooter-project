#pragma once

// stdlib
#include <iostream>

// GLFW
#define GLFW_DLL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

extern char* WindowTitle;
extern int WindowWidth;
extern int WindowHeight;

struct Vec2
{
	float x, y;
};

struct Vec3
{
	float x, y, z;
};

struct Vec4
{
	float x, y, z, w;
};

struct Mesh
{
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
};

struct ColorVertex
{
	Vec3 pos;
	Vec4 color;
};

struct TextureVertex
{
	Vec3 pos;
	Vec2 texPos;
};
