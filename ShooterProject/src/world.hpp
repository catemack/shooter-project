#pragma once

#include "common.hpp"

// GLFW
#define GLFW_DLL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <entities/renderable.hpp>
#include <entities/color_entity.hpp>
#include <entities/texture_entity.hpp>
#include <entities/player.hpp>
#include <entities/wall.hpp>
#include <entities/bullet.hpp>

#include <utils/camera.hpp>

class World
{
public:
	World();
	~World();

	bool init();
	void bindInputHandlers(GLFWwindow* window);
	void render();
	void update(float deltaTime);

private:
	void handleKey(GLFWwindow* window, int key, int scancode, int action, int mods);
	void handleMouseClick(GLFWwindow* window, int button, int action, int mods);
	void handleMouseMove(GLFWwindow* window, double xpos, double ypos);

	std::vector<std::unique_ptr<Renderable>> renderables;
	std::vector<std::unique_ptr<Wall>> walls;
	std::vector<std::unique_ptr<Bullet>> bullets;

	Player player;

	// keypress bools
	bool pressedForward;
	bool pressedBackward;
	bool pressedLeft;
	bool pressedRight;

	// mouse position
	float lastX;
	float lastY;
	bool firstMouseUpdate; // ensures mouse doesn't jump when window initializes
};
