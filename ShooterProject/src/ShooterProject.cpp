// ShooterProject.cpp : Defines the entry point for the application.
//

#include "ShooterProject.hpp"

float lastTime;
float deltaTime;

int main()
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, 0);

	/* Anti-aliasing */
	glfwWindowHint(GLFW_SAMPLES, 4);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WindowWidth, WindowHeight, WindowTitle, NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		fprintf(stderr, "Window failed to initialize");
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Attach window size handler */
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

	/* vsync */
	glfwSwapInterval(1);

	/* Initialize GLAD */
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwTerminate();
		fprintf(stderr, "GLAD failed to initialize");
		return -1;
	}

	/* Configure global OpenGL state */
	glEnable(GL_DEPTH_TEST);

	/* Initialize the world */
	World world;
	if (!world.init())
	{
		glfwTerminate();
		fprintf(stderr, "World failed to initialize");
		return -1;
	}

	/* Bind inputs */
	world.bindInputHandlers(window);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Poll for and process events */
		glfwPollEvents();

		/* Update delta time */
		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		/* Update the world */
		world.update(deltaTime);

		/* Clear screen */
		glClearColor(0.26f, 0.50f, 0.96f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* Render the world */
		world.render();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

void frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
