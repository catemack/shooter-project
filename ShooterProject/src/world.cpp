#include "world.hpp"

World::World() :
	pressedForward(false),
	pressedBackward(false),
	pressedLeft(false),
	pressedRight(false),
	lastX(WindowWidth / 2.0f),
	lastY(WindowHeight / 2.0f),
	firstMouseUpdate(true),
	player(glm::vec3(0.0f, 0.0f, 3.0f))
{
}

World::~World()
{
	for (auto entity : renderables)
		delete entity;
}

bool World::init()
{
	ColorVertex vertices[] = {
		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f) },
		{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f) },
		{ glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f) },
		{ glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f) },
		{ glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f) },
		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f)  },

		{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f) },
		{ glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f) },
		{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f) },
		{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f) },
		{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f) },
		{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f) },

		{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f) },
		{ glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f) },
		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f) },
		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f) },
		{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f) },
		{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f) },

		{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f) },
		{ glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f) },
		{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f) },
		{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f) },
		{ glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f) },
		{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f) },

		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f) },
		{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f) },
		{ glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f) },
		{ glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f) },
		{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f) },
		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f) },

		{ glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f) },
		{ glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f) },
		{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f) },
		{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f) },
		{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f) },
		{ glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f) }
	};

	renderables.push_back(new ColorEntity(glm::vec3(0.0f, 0.0f, 0.0f), vertices, 36, "lit_color", "lit_color"));

	glm::vec3 lightVerts[] = {
		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3(0.5f, -0.5f, -0.5f),
		glm::vec3(0.5f, 0.5f, -0.5f),
		glm::vec3(0.5f, 0.5f, -0.5f),
		glm::vec3(-0.5f, 0.5f, -0.5f),
		glm::vec3(-0.5f, -0.5f, -0.5f),

		glm::vec3(-0.5f, -0.5f, 0.5f),
		glm::vec3(0.5f, -0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(-0.5f, 0.5f, 0.5f),
		glm::vec3(-0.5f, -0.5f, 0.5f),

		glm::vec3(-0.5f, 0.5f, 0.5f),
		glm::vec3(-0.5f, 0.5f, -0.5f),
		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3(-0.5f, -0.5f, 0.5f),
		glm::vec3(-0.5f, 0.5f, 0.5f),

		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, -0.5f),
		glm::vec3(0.5f, -0.5f, -0.5f),
		glm::vec3(0.5f, -0.5f, -0.5f),
		glm::vec3(0.5f, -0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f),

		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3(0.5f, -0.5f, -0.5f),
		glm::vec3(0.5f, -0.5f, 0.5f),
		glm::vec3(0.5f, -0.5f, 0.5f),
		glm::vec3(-0.5f, -0.5f, 0.5f),
		glm::vec3(-0.5f, -0.5f, -0.5f),

		glm::vec3(-0.5f, 0.5f, -0.5f),
		glm::vec3(0.5f, 0.5f, -0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(-0.5f, 0.5f, 0.5f),
		glm::vec3(-0.5f, 0.5f, -0.5f)
	};

	renderables.push_back(new ColorEntity(glm::vec3(5.0f, 0.0f, 0.0f), glm::vec4(1.0, 1.0, 1.0, 1.0), lightVerts, 36, "color", "color"));

	std::array<std::array<glm::vec3, 4>, 6> wallBounds;
	wallBounds[0] = {
		glm::vec3(0.5, -0.5, -1.0),
		glm::vec3(-0.5, -0.5, -1.0),
		glm::vec3(0.5, 0.5, -1.0),
		glm::vec3(-0.5, 0.5, -1.0)
	};
	wallBounds[1] = {
		glm::vec3(0.5, -0.5, 1.0),
		glm::vec3(-0.5, -0.5, 1.0),
		glm::vec3(0.5, 0.5, 1.0),
		glm::vec3(-0.5, 0.5, 1.0)
	};
	wallBounds[2] = {
		glm::vec3(-0.5, 0.5, -1.0),
		glm::vec3(-0.5, 0.5, 1.0),
		glm::vec3(-0.5, -0.5, -1.0),
		glm::vec3(-0.5, -0.5, 1.0)
	};
	wallBounds[3] = {
		glm::vec3(0.5, 0.5, -1.0),
		glm::vec3(0.5, 0.5, 1.0),
		glm::vec3(0.5, -0.5, -1.0),
		glm::vec3(0.5, -0.5, 1.0)
	};
	wallBounds[4] = {
		glm::vec3(0.5, -0.5, -1.0),
		glm::vec3(-0.5, -0.5, -1.0),
		glm::vec3(0.5, -0.5, 1.0),
		glm::vec3(-0.5, -0.5, 1.0)
	};
	wallBounds[5] = {
		glm::vec3(0.5, 0.5, -1.0),
		glm::vec3(-0.5, 0.5, -1.0),
		glm::vec3(0.5, 0.5, 1.0),
		glm::vec3(-0.5, 0.5, 1.0)
	};
	walls.push_back(new Wall(glm::vec3(-5.0, 0.0, 0.0), glm::vec4(0.2, 0.2, 0.2, 1.0), wallBounds));

	return true;
}

void World::update(float deltaTime)
{
	float forward = 0.0f;
	float right = 0.0f;

	if (pressedForward)
		forward += deltaTime;
	if (pressedBackward)
		forward -= deltaTime;
	if (pressedLeft)
		right -= deltaTime;
	if (pressedRight)
		right += deltaTime;

	player.move(forward, right);

	// Handle collisions
	for (auto wall : walls)
	{
		if (wall->intersects(player))
		{
			//std::cout << "intersection" << std::endl;
		}
	}
}

void World::bindInputHandlers(GLFWwindow* window)
{
	// Set context to be used by input callbacks
	glfwSetWindowUserPointer(window, this);

	// Bind keyboard input
	auto keyRedirect = [](GLFWwindow * wnd, int _0, int _1, int _2, int _3) { ((World*)glfwGetWindowUserPointer(wnd))->handleKey(wnd, _0, _1, _2, _3); };
	glfwSetKeyCallback(window, keyRedirect);

	// Bind mouse input
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	auto cursorRedirect = [](GLFWwindow * wnd, double _0, double _1) { ((World*)glfwGetWindowUserPointer(wnd))->handleMouseMove(wnd, _0, _1); };
	glfwSetCursorPosCallback(window, cursorRedirect);
}

void World::render()
{
	for (auto renderable : renderables) {
		renderable->draw(player.getCamera(), glm::vec3(1.0f, 1.0f, 1.0f), 0.5f);
	}

	for (auto wall : walls) {
		wall->draw(player.getCamera(), glm::vec3(1.0f, 1.0f, 1.0f), 0.5f);
	}
}

void World::handleKey(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	// Close game when pressing ESC
	if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE)
		glfwSetWindowShouldClose(window, GL_TRUE);

	// Directional inputs, value used in update
	if (key == GLFW_KEY_W)
		pressedForward = !(action == GLFW_RELEASE);

	if (key == GLFW_KEY_S)
		pressedBackward = !(action == GLFW_RELEASE);

	if (key == GLFW_KEY_A)
		pressedLeft = !(action == GLFW_RELEASE);

	if (key == GLFW_KEY_D)
		pressedRight = !(action == GLFW_RELEASE);
}

void World::handleMouseMove(GLFWwindow* window, double xpos, double ypos)
{
	// Don't update camera on first update so the view doesn't suddenly jump
	if (firstMouseUpdate)
	{
		firstMouseUpdate = false;
		lastX = float(xpos);
		lastY = float(ypos);
	}

	float deltaX = float(xpos) - lastX;
	float deltaY = lastY - float(ypos);
	lastX = float(xpos);
	lastY = float(ypos);

	player.look(deltaX, deltaY);
}
