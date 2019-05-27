#include "color_entity.hpp"

const std::string ColorEntity::VSShaderPath("./shaders/color.vs.glsl");
const std::string ColorEntity::FSShaderPath("./shaders/color.fs.glsl");

ColorEntity::ColorEntity(glm::vec3 position, ColorVertex vertices[], GLuint triangles[], int size)
{
	pos = position;

	/* Set up vertex array object, vertex buffer, element buffer */
	glGenVertexArrays(1, &mesh.vao);
	glGenBuffers(1, &mesh.vbo);
	//glGenBuffers(1, &mesh.ebo);

	/* Bind Vertex Array Object */
	glBindVertexArray(mesh.vao);

	/* Bind and set vertex buffer */
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ColorVertex) * size, vertices, GL_STATIC_DRAW);

	/* Bind and set element buffer */
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * size, triangles, GL_STATIC_DRAW);*/

	/* Input data from vertex buffer */
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)sizeof(glm::vec3));
}

ColorEntity::~ColorEntity()
{
	glDeleteVertexArrays(1, &mesh.vao);
	glDeleteBuffers(1, &mesh.vbo);
	//glDeleteBuffers(1, &mesh.ebo);
}

bool ColorEntity::init()
{
	return shader.init(VSShaderPath.c_str(), FSShaderPath.c_str());
}

void ColorEntity::draw(const Camera& camera)
{
	/* Set transform matrix */
	glm::mat4 transform = glm::mat4(5.0f);
	transform = glm::translate(transform, pos);

	/* Set projection matrix */
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WindowWidth / (float)WindowHeight, 0.1f, 100.0f);

	/* Set view matrix */
	glm::mat4 view = camera.getViewMatrix();

	/* Set shaders */
	shader.use();

	/* Set vertices and indices */
	glBindVertexArray(mesh.vao);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);

	GLuint viewLoc = glGetUniformLocation(shader.program, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	GLuint transformLoc = glGetUniformLocation(shader.program, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

	GLuint projectionLoc = glGetUniformLocation(shader.program, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glm::vec4 out = projection * view * transform * glm::vec4(-0.5f, 0.5f, 0.5f, 1.0f);
	std::cout << glm::to_string(out) << std::endl;

	/* Draw triangles */
	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
