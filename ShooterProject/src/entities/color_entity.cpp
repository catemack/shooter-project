#include "color_entity.hpp"

const std::string ColorEntity::VSShaderPath("./shaders/color.vs.glsl");
const std::string ColorEntity::FSShaderPath("./shaders/color.fs.glsl");

ColorEntity::ColorEntity(const glm::vec3 position, const ColorVertex vertices[], const int size, const std::string vsShader, const std::string fsShader) :
	Renderable(vsShader, fsShader)
{
	init(position, vertices, size, vsShader, fsShader);
}

ColorEntity::ColorEntity(glm::vec3 position, ColorVertex vertices[], const int size) :
	Renderable("color", "color")
{
	init(position, vertices, size, "color", "color");
}

ColorEntity::ColorEntity(glm::vec3 position, glm::vec4 color, glm::vec3 vertices[], const int size, const std::string vsShader, const std::string fsShader) :
	Renderable(vsShader, fsShader)
{
	ColorVertex* cVertices = new ColorVertex[size];

	for (int i = 0; i < size; ++i)
	{

		cVertices[i].pos = vertices[i];
		cVertices[i].color = color;
	}

	init(position, cVertices, size, vsShader, fsShader);

	delete[] cVertices;
}

void ColorEntity::init(const glm::vec3 position, const ColorVertex vertices[], const int size, const std::string vsShader, const std::string fsShader)
{
	pos = position;
	setVertexArrays(vertices, size);
}

void ColorEntity::draw(const Camera& camera)
{
	draw(camera, glm::vec3(1.0, 1.0, 1.0), 1.0);
}

void ColorEntity::draw(const Camera& camera, const glm::vec3 lightColor, const float lightIntensity)
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

	shader.setMat4("view", view);
	shader.setMat4("transform", transform);
	shader.setMat4("projection", projection);

	shader.setVec3("ambientLightColor", lightColor);
	shader.setFloat("ambientLightStrength", lightIntensity);

	/* Draw triangles */
	glDrawArrays(GL_TRIANGLES, 0, 36);
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(ColorVertex), (void*)sizeof(glm::vec3));
}
