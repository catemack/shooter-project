#include "wall.hpp"

// wallBounds is a rectangular prism, faces should be ordered:
// front, back, left, right, down, up
Wall::Wall(glm::vec3 position, glm::vec4 color, std::array<std::array<glm::vec3, 4>, 6> wallBounds) :
	//Renderable::pos(position),
	Collidable(position, wallBounds),
	Renderable("lit_color", "lit_color")
{
	Renderable::pos = position;

	ColorVertex vertices[36] = {
		{ wallBounds[0][0], glm::vec3(0.0f, 0.0f, -1.0f), color },
		{ wallBounds[0][1], glm::vec3(0.0f, 0.0f, -1.0f), color },
		{ wallBounds[0][2], glm::vec3(0.0f, 0.0f, -1.0f), color },
		{ wallBounds[0][2], glm::vec3(0.0f, 0.0f, -1.0f), color },
		{ wallBounds[0][3], glm::vec3(0.0f, 0.0f, -1.0f), color },
		{ wallBounds[0][1], glm::vec3(0.0f, 0.0f, -1.0f), color },

		{ wallBounds[1][0], glm::vec3(0.0f, 0.0f, 1.0f), color },
		{ wallBounds[1][1], glm::vec3(0.0f, 0.0f, 1.0f), color },
		{ wallBounds[1][2], glm::vec3(0.0f, 0.0f, 1.0f), color },
		{ wallBounds[1][2], glm::vec3(0.0f, 0.0f, 1.0f), color },
		{ wallBounds[1][3], glm::vec3(0.0f, 0.0f, 1.0f), color },
		{ wallBounds[1][1], glm::vec3(0.0f, 0.0f, 1.0f), color },

		{ wallBounds[2][0], glm::vec3(-1.0f, 0.0f, 0.0f), color },
		{ wallBounds[2][1], glm::vec3(-1.0f, 0.0f, 0.0f), color },
		{ wallBounds[2][2], glm::vec3(-1.0f, 0.0f, 0.0f), color },
		{ wallBounds[2][2], glm::vec3(-1.0f, 0.0f, 0.0f), color },
		{ wallBounds[2][3], glm::vec3(-1.0f, 0.0f, 0.0f), color },
		{ wallBounds[2][1], glm::vec3(-1.0f, 0.0f, 0.0f), color },

		{ wallBounds[3][0], glm::vec3(1.0f, 0.0f, 0.0f), color },
		{ wallBounds[3][1], glm::vec3(1.0f, 0.0f, 0.0f), color },
		{ wallBounds[3][2], glm::vec3(1.0f, 0.0f, 0.0f), color },
		{ wallBounds[3][2], glm::vec3(1.0f, 0.0f, 0.0f), color },
		{ wallBounds[3][3], glm::vec3(1.0f, 0.0f, 0.0f), color },
		{ wallBounds[3][1], glm::vec3(1.0f, 0.0f, 0.0f), color },

		{ wallBounds[4][0], glm::vec3(0.0f, -1.0f, 0.0f), color },
		{ wallBounds[4][1], glm::vec3(0.0f, -1.0f, 0.0f), color },
		{ wallBounds[4][2], glm::vec3(0.0f, -1.0f, 0.0f), color },
		{ wallBounds[4][2], glm::vec3(0.0f, -1.0f, 0.0f), color },
		{ wallBounds[4][3], glm::vec3(0.0f, -1.0f, 0.0f), color },
		{ wallBounds[4][1], glm::vec3(0.0f, -1.0f, 0.0f), color },

		{ wallBounds[5][0], glm::vec3(0.0f, 1.0f, 0.0f), color },
		{ wallBounds[5][1], glm::vec3(0.0f, 1.0f, 0.0f), color },
		{ wallBounds[5][2], glm::vec3(0.0f, 1.0f, 0.0f), color },
		{ wallBounds[5][2], glm::vec3(0.0f, 1.0f, 0.0f), color },
		{ wallBounds[5][3], glm::vec3(0.0f, 1.0f, 0.0f), color },
		{ wallBounds[5][1], glm::vec3(0.0f, 1.0f, 0.0f), color },
	};

	/* Set up vertex array object, vertex buffer */
	glGenVertexArrays(1, &mesh.vao);
	glGenBuffers(1, &mesh.vbo);

	/* Bind Vertex Array Object */
	glBindVertexArray(mesh.vao);

	/* Bind and set vertex buffer */
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ColorVertex) * 36, vertices, GL_STATIC_DRAW);

	/* Input data from vertex buffer */
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)(2 * sizeof(glm::vec3)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)sizeof(glm::vec3));
}

void Wall::draw(const Camera& camera)
{
	draw(camera, glm::vec3(1.0, 1.0, 1.0), 1.0);
}

void Wall::draw(const Camera& camera, const glm::vec3 lightColor, const float lightIntensity)
{
	/* Set transform matrix */
	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, Renderable::pos);

	/* Set projection matrix */
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WindowWidth / (float)WindowHeight, 0.1f, 100.0f);

	/* Set view matrix */
	glm::mat4 view = camera.getViewMatrix();

	/* Set normal matrix */
	glm::mat3 normal = glm::mat3(glm::transpose(glm::inverse(transform)));

	/* Set shaders */
	shader.use();

	/* Set vertices and indices */
	glBindVertexArray(mesh.vao);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);

	shader.setMat4("view", view);
	shader.setMat4("transform", transform);
	shader.setMat4("projection", projection);
	shader.setMat3("normal_mat", normal);

	shader.setVec3("ambient_light_color", lightColor);
	shader.setFloat("ambient_light_strength", lightIntensity);

	shader.setVec3("view_pos", camera.getPos());

	/* Draw triangles */
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
