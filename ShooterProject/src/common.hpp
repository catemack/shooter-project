#pragma once

// stdlib
#include <string>

const char* WindowTitle = "My Game";
const int WindowWidth = 1280;
const int WindowHeight = 720;

struct Mesh
{
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
};
