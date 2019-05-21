#pragma once

// stdlib
#include <vector>

// GLFW
#define GLFW_DLL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <entities/renderable.hpp>
#include <entities/color_entity.hpp>
#include <entities/texture_entity.hpp>

class World
{
public:
	~World();

	bool init();
	void bindInputHandlers(GLFWwindow* window);
	void render();

private:
	void handleKey(GLFWwindow* window, int key, int scancode, int action, int mods);

	std::vector<Renderable*> renderables;
};
