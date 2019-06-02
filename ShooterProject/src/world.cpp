#include "world.hpp"

World::World() :
	pressedForward(false),
	pressedBackward(false),
	pressedLeft(false),
	pressedRight(false),
	lastX(WindowWidth / 2),
	lastY(WindowHeight / 2),
	firstMouseUpdate(true)
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
		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f) },
		{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f) },
		{ glm::vec3(0.5f, 0.5f, -0.5f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f) },
		{ glm::vec3(0.5f, 0.5f, -0.5f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f) },
		{ glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f) },
		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f) },

		{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f) },
		{ glm::vec3(0.5f, -0.5f, 0.5f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f) },
		{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f) },
		{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f) },
		{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f) },
		{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f) },

		{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f) },
		{ glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f) },
		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f) },
		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f) },
		{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f) },
		{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f) },

		{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f) },
		{ glm::vec3(0.5f, 0.5f, -0.5f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f) },
		{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f) },
		{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f) },
		{ glm::vec3(0.5f, -0.5f, 0.5f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f) },
		{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f) },

		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f) },
		{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f) },
		{ glm::vec3(0.5f, -0.5f, 0.5f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f) },
		{ glm::vec3(0.5f, -0.5f, 0.5f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f) },
		{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f) },
		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f) },

		{ glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f) },
		{ glm::vec3(0.5f, 0.5f, -0.5f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f) },
		{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f) },
		{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f) },
		{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f) },
		{ glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec4(0.85f, 0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f) }
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

	/*renderables.push_back(new TextureEntity);
	if (!((TextureEntity*)renderables.back())->init("./data/textures/awesomeface.png"))
		return false;*/

	return true;
}

void World::update(float deltaTime)
{
	float cameraSpeed = 2.5f * deltaTime;

	// Create a normalized projection of camera.front on the XZ axis
	// This keeps the player bound to only moving horizontally with WASD
	glm::vec3 front = glm::vec3(camera.front.x, 0.0f, camera.front.z);
	front = glm::normalize(front);

	if (pressedForward)
		camera.pos += cameraSpeed * front;
	if (pressedBackward)
		camera.pos -= cameraSpeed * front;
	if (pressedLeft)
		camera.pos -= cameraSpeed * glm::normalize(glm::cross(front, camera.up));
	if (pressedRight)
		camera.pos += cameraSpeed * glm::normalize(glm::cross(front, camera.up));
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
		renderable->draw(camera, glm::vec3(1.0f, 1.0f, 1.0f), 0.5f);
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
	if (firstMouseUpdate)
	{
		firstMouseUpdate = false;
		lastX = xpos;
		lastY = ypos;
	}

	float deltaX = xpos - lastX;
	float deltaY = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.05f;
	deltaX *= sensitivity;
	deltaY *= sensitivity;

	camera.yaw += deltaX;
	camera.pitch += deltaY;

	// Bind pitch range so we can't do flips (yet)
	if (camera.pitch > 89.0f)
		camera.pitch = 89.0f;
	if (camera.pitch < -89.0f)
		camera.pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));
	front.y = sin(glm::radians(camera.pitch));
	front.z = sin(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));
	camera.front = glm::normalize(front);
}
