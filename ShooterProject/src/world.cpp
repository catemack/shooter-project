#include "world.hpp"

World::~World()
{
	for (auto entity : renderables)
		delete entity;
}

bool World::init()
{
	renderables.push_back(new ColorEntity);
	if (!((ColorEntity*)renderables.back())->init())
		return false;

	renderables.push_back(new TextureEntity);
	if (!((TextureEntity*)renderables.back())->init("./data/textures/awesomeface.png"))
		return false;

	return true;
}

void World::bindInputHandlers(GLFWwindow* window)
{
	auto key_redirect = [](GLFWwindow * wnd, int _0, int _1, int _2, int _3) { ((World*)glfwGetWindowUserPointer(wnd))->handleKey(wnd, _0, _1, _2, _3); };
	glfwSetKeyCallback(window, key_redirect);
}

void World::render()
{
	for (auto renderable : renderables)
		renderable->draw();
}

void World::handleKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE)
		glfwSetWindowShouldClose(window, GL_TRUE);
}
