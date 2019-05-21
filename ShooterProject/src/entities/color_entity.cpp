#include "color_entity.hpp"

const std::string ColorEntity::VSShaderPath("./shaders/color.vs.glsl");
const std::string ColorEntity::FSShaderPath("./shaders/color.fs.glsl");

ColorEntity::ColorEntity()
{
	// TODO: generate this from arguments
	ColorVertex vertices[4];
	vertices[0].pos = { 0.0f, 0.5f, 0.0f };
	vertices[0].color = { 1.0f, 0.0f, 0.0f };
	vertices[1].pos = { 0.0f, -0.5f, 0.0f };
	vertices[1].color = { 0.0f, 1.0f, 0.0f };
	vertices[2].pos = { -0.5f, -0.5f, 0.0f };
	vertices[2].color = { 0.0f, 0.0f, 1.0f };
	vertices[3].pos = { -0.5f,  0.5f, 0.0f };
	vertices[3].color = { 1.0f, 1.0f, 1.0f };

	unsigned int indices[] = {
		0, 3, 1,  // first Triangle
		1, 3, 2   // second Triangle
	};

	/* Set up vertex array object, vertex buffer, element buffer */
	glGenVertexArrays(1, &mesh.vao);
	glGenBuffers(1, &mesh.vbo);
	glGenBuffers(1, &mesh.ebo);

	/* Bind Vertex Array Object */
	glBindVertexArray(mesh.vao);

	/* Bind and set vertex buffer */
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/* Bind and set element buffer */
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

ColorEntity::~ColorEntity()
{
	glDeleteVertexArrays(1, &mesh.vao);
	glDeleteBuffers(1, &mesh.vbo);
	glDeleteBuffers(1, &mesh.ebo);
}

bool ColorEntity::init()
{
	return shader.init(VSShaderPath.c_str(), FSShaderPath.c_str());
}

void ColorEntity::draw()
{
	/* Set shaders */
	shader.use();

	/* Set vertices and indices */
	glBindVertexArray(mesh.vao);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);

	/* Input data from vertex buffer */
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)sizeof(Vec3));

	/* Draw triangles */
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

