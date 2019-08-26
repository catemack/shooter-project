#include "color_entity.hpp"

ColorEntity::ColorEntity(const glm::vec3 position, const std::vector<ColorVertex> vertices, const std::string vsShader, const std::string fsShader) :
	Renderable(vsShader, fsShader)
{
	pos = position;
	setVertexArrays(vertices);
}

void ColorEntity::draw(const Camera& camera)
{
	draw(camera, glm::vec3(1.0, 1.0, 1.0), 1.0);
}

void ColorEntity::draw(const Camera& camera, const glm::vec3 lightColor, const float lightIntensity)
{
	/* Set transform matrix */
	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, pos);

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

	glm::vec3 diffLightPos = glm::vec3(2.5f, 0.0f, 5.0f);
	glm::vec3 diffLightColor = glm::vec3(1.0f, 1.0f, 1.0f);

	shader.setVec3("light_pos", diffLightPos);
	shader.setVec3("light_color", diffLightColor);

	shader.setVec3("ambient_light_color", lightColor);
	shader.setFloat("ambient_light_strength", lightIntensity);

	shader.setVec3("view_pos", camera.getPos());

	/* Draw triangles */
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void ColorEntity::setVertexArrays(const std::vector<ColorVertex> vertices)
{
	setVertexArrays(&vertices.front(), vertices.size());
}

void ColorEntity::setVertexArrays(const ColorVertex vertices[], const int size)
{
	/* Set up vertex array object, vertex buffer */
	glGenVertexArrays(1, &mesh.vao);
	glGenBuffers(1, &mesh.vbo);

	/* Bind Vertex Array Object */
	glBindVertexArray(mesh.vao);

	/* Bind and set vertex buffer */
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ColorVertex) * size, vertices, GL_STATIC_DRAW);

	/* Input data from vertex buffer */
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)(2 * sizeof(glm::vec3)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)sizeof(glm::vec3));
}
