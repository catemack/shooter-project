#include "world.hpp"

World::World() :
	pressedForward(false),
	pressedBackward(false),
	pressedLeft(false),
	pressedRight(false),
	lastX(WindowWidth / 2),
	lastY(WindowHeight / 2)
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
		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ glm::vec3(0.5f, 0.5f, -0.5f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) },
		{ glm::vec3(0.5f, 0.5f, -0.5f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) },
		{ glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) },

		{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ glm::vec3(0.5f, -0.5f, 0.5f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) },
		{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) },
		{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) },

		{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) },
		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f) },

		{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ glm::vec3(0.5f, 0.5f, -0.5f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) },
		{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ glm::vec3(0.5f, -0.5f, 0.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f) },

		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) },
		{ glm::vec3(0.5f, -0.5f, 0.5f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ glm::vec3(0.5f, -0.5f, 0.5f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) },

		{ glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ glm::vec3(0.5f, 0.5f, -0.5f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) },
		{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) }
	};
	GLuint triangles[]{
		7, 6, 5,
		5, 4, 7,
		3, 2, 1,
		1, 0, 3,
		0, 4, 7,
		7, 3, 0,
		1, 5, 6,
		6, 2, 1,
		7, 6, 2,
		2, 3, 7,
		4, 5, 1,
		1, 0, 4
	};
	renderables.push_back(new ColorEntity(glm::vec3(0.0f, 0.0f, 0.0f), vertices, triangles, 36));
	if (!((ColorEntity*)renderables.back())->init())
		return false;

	/*renderables.push_back(new TextureEntity);
	if (!((TextureEntity*)renderables.back())->init("./data/textures/awesomeface.png"))
		return false;*/

	return true;
}

void World::update(float deltaTime)
{
	float cameraSpeed = 2.5f * deltaTime;
	if (pressedForward)
		camera.pos += cameraSpeed * camera.front;
	if (pressedBackward)
		camera.pos -= cameraSpeed * camera.front;
	if (pressedLeft)
		camera.pos -= cameraSpeed * glm::normalize(glm::cross(camera.front, camera.up));
	if (pressedRight)
		camera.pos += cameraSpeed * glm::normalize(glm::cross(camera.front, camera.up));
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
	for (auto renderable : renderables)
		renderable->draw(camera);
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

}
