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
}

bool World::init()
{
	std::vector<ColorVertex> vertices {
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

	auto renderable = std::make_unique<ColorEntity>(glm::vec3(0.0f, 0.0f, 0.0f), vertices, "lit_color", "lit_color");
	renderables.push_back(std::move(renderable));

	std::vector<ColorVertex> lightVerts {
		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec4(1.0, 1.0, 1.0, 1.0) },
		{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec4(1.0, 1.0, 1.0, 1.0) },
		{ glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec4(1.0, 1.0, 1.0, 1.0) },
		{ glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec4(1.0, 1.0, 1.0, 1.0) },
		{ glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec4(1.0, 1.0, 1.0, 1.0) },
		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec4(1.0, 1.0, 1.0, 1.0)  },

		{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec4(1.0, 1.0, 1.0, 1.0) },
		{ glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec4(1.0, 1.0, 1.0, 1.0) },
		{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec4(1.0, 1.0, 1.0, 1.0) },
		{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec4(1.0, 1.0, 1.0, 1.0) },
		{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec4(1.0, 1.0, 1.0, 1.0) },
		{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec4(1.0, 1.0, 1.0, 1.0) },

		{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec4(1.0, 1.0, 1.0, 1.0) },
		{ glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec4(1.0, 1.0, 1.0, 1.0) },
		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec4(1.0, 1.0, 1.0, 1.0) },
		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec4(1.0, 1.0, 1.0, 1.0) },
		{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec4(1.0, 1.0, 1.0, 1.0) },
		{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec4(1.0, 1.0, 1.0, 1.0) },

		{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec4(1.0, 1.0, 1.0, 1.0) },
		{ glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec4(1.0, 1.0, 1.0, 1.0) },
		{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec4(1.0, 1.0, 1.0, 1.0) },
		{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec4(1.0, 1.0, 1.0, 1.0) },
		{ glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec4(1.0, 1.0, 1.0, 1.0) },
		{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec4(1.0, 1.0, 1.0, 1.0) },

		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec4(1.0, 1.0, 1.0, 1.0) },
		{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec4(1.0, 1.0, 1.0, 1.0) },
		{ glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec4(1.0, 1.0, 1.0, 1.0) },
		{ glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec4(1.0, 1.0, 1.0, 1.0) },
		{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec4(1.0, 1.0, 1.0, 1.0) },
		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec4(1.0, 1.0, 1.0, 1.0) },

		{ glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec4(1.0, 1.0, 1.0, 1.0) },
		{ glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec4(1.0, 1.0, 1.0, 1.0) },
		{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec4(1.0, 1.0, 1.0, 1.0) },
		{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec4(1.0, 1.0, 1.0, 1.0) },
		{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec4(1.0, 1.0, 1.0, 1.0) },
		{ glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec4(1.0, 1.0, 1.0, 1.0) }
	};

	auto light = std::make_unique<ColorEntity>(glm::vec3(5.0f, 0.0f, 0.0f), lightVerts, "color", "color");
	renderables.push_back(std::move(light));

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

	auto wall = std::make_unique<Wall>(glm::vec3(-5.0, 0.0, 0.0), glm::vec4(0.2, 0.2, 0.2, 1.0), wallBounds);
	walls.push_back(std::move(wall));

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

	for (auto& bullet : bullets)
		bullet->move(deltaTime);

	// Handle wall collisions
	for (auto const& wall : walls)
	{
		if (wall->intersects(player))
			player.resolveCollision(*wall);

		for (auto bullet = bullets.begin(); bullet != bullets.end(); )
		{
			if (!(*bullet)->shouldCleanUp() && wall->intersects(**bullet))
				(*bullet)->resolveCollision(*wall);

			if ((*bullet)->shouldCleanUp())
				bullet = bullets.erase(bullet);
			else
				++bullet;
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

	// Bind mouse buttons
	auto mouseRedirect = [](GLFWwindow* wnd, int _0, int _1, int _2) { ((World*)glfwGetWindowUserPointer(wnd))->handleMouseClick(wnd, _0, _1, _2); };
	glfwSetMouseButtonCallback(window, mouseRedirect);

	// Bind mouse input
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	auto cursorRedirect = [](GLFWwindow * wnd, double _0, double _1) { ((World*)glfwGetWindowUserPointer(wnd))->handleMouseMove(wnd, _0, _1); };
	glfwSetCursorPosCallback(window, cursorRedirect);
}

void World::render()
{
	for (auto const& renderable : renderables) {
		renderable->draw(player.getCamera(), glm::vec3(1.0f, 1.0f, 1.0f), 0.5f);
	}

	for (auto const& wall : walls) {
		wall->draw(player.getCamera(), glm::vec3(1.0f, 1.0f, 1.0f), 0.5f);
	}

	for (auto const& bullet : bullets) {
		bullet->draw(player.getCamera(), glm::vec3(1.0f, 1.0f, 1.0f), 0.5f);
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

void World::handleMouseClick(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_RELEASE)
	{
		auto bullet = player.fire();
		bullets.push_back(std::move(bullet));
	}
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
