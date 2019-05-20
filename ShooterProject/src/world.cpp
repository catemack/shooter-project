#include "world.hpp"

World::World()
{
}

World::~World()
{
}

void World::bindInputHandlers(GLFWwindow* window)
{
	auto key_redirect = [](GLFWwindow * wnd, int _0, int _1, int _2, int _3) { ((World*)glfwGetWindowUserPointer(wnd))->handleKey(wnd, _0, _1, _2, _3); };
	glfwSetKeyCallback(window, key_redirect);
}

void World::render(GLFWwindow* window, const Effect* effect)
{
	
}

void World::handleKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE)
		glfwSetWindowShouldClose(window, GL_TRUE);
}
