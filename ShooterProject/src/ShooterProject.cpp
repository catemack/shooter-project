// ShooterProject.cpp : Defines the entry point for the application.
//

#include "ShooterProject.hpp"

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

	/* Initialize the world */
	World world;

	/* Bind inputs */
	world.bindInputHandlers(window);

	/* TODO: move shader and mesh init to a Renderable class */

	/* Rectangles */
	float colorVertices[] = {
		 0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // top right
		 0.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom left
		-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f  // top left 
	};
	float texVertices[] = {
		 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
		 0.0f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
		 0.0f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = {
		0, 3, 1,  // first Triangle
		1, 3, 2   // second Triangle
	};

	/* Load shaders */
	const char* colorVS = "./shaders/color.vs.glsl";
	const char* colorFS = "./shaders/color.fs.glsl";
	Shader colorShader;
	if (!colorShader.init(colorVS, colorFS))
		return -1;

	const char* textureVS = "./shaders/texture.vs.glsl";
	const char* textureFS = "./shaders/texture.fs.glsl";
	Shader textureShader;
	if (!textureShader.init(textureVS, textureFS))
		return -1;

	const char* testVS = "./shaders/test.vs.glsl";
	const char* testFS = "./shaders/test.fs.glsl";
	Shader testShader;
	if (!testShader.init(testVS, testFS))
		return -1;

	/* Set up vertex array object, vertex buffer, element buffer */
	Mesh mesh;
	glGenVertexArrays(1, &mesh.vao);
	glGenBuffers(1, &mesh.vbo);
	glGenBuffers(1, &mesh.ebo);

	/* Bind Vertex Array Object */
	glBindVertexArray(mesh.vao);

	/* Bind and set vertex buffer */
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colorVertices), colorVertices, GL_STATIC_DRAW);

	/* Bind and set element buffer */
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	/* Set vertex attribute pointers */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	Mesh texMesh;
	glGenVertexArrays(1, &texMesh.vao);
	glGenBuffers(1, &texMesh.vbo);
	glGenBuffers(1, &texMesh.ebo);

	/* Bind Vertex Array Object */
	glBindVertexArray(texMesh.vao);

	/* Bind and set vertex buffer */
	glBindBuffer(GL_ARRAY_BUFFER, texMesh.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texVertices), texVertices, GL_STATIC_DRAW);

	/* Bind and set element buffer */
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, texMesh.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	/* Set vertex attribute pointers */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/* Load textures */
	Texture texture;
	if (!texture.init("./data/textures/awesomeface.png"))
		return -1;

	/* Tell OpenGL which texture unit each sampler belongs to */
	textureShader.use();
	glUniform1i(glGetUniformLocation(textureShader.program, "sampler0"), 0);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClearColor(0.26f, 0.50f, 0.96f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//world.render(window, &effect);
		colorShader.use();
		glBindVertexArray(mesh.vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// Bind textures on corresponding texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture.id);

		// Render container
		textureShader.use();
		glBindVertexArray(texMesh.vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &mesh.vao);
	glDeleteBuffers(1, &mesh.vbo);
	glDeleteBuffers(1, &mesh.ebo);

	glDeleteVertexArrays(1, &texMesh.vao);
	glDeleteBuffers(1, &texMesh.vbo);
	glDeleteBuffers(1, &texMesh.ebo);

	glfwTerminate();
	return 0;
}

void frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
