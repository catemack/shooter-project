#pragma once

// GLFW
#define GLFW_DLL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// internal
#include <shader.hpp>

class World
{
public:
	World();
	~World();

	void bindInputHandlers(GLFWwindow* window);
	void render(GLFWwindow* window, const Shader* shader);

private:
	void handleKey(GLFWwindow* window, int key, int scancode, int action, int mods);
};
