#include "texture_entity.hpp"

const std::string TextureEntity::VSShaderPath("./shaders/texture.vs.glsl");
const std::string TextureEntity::FSShaderPath("./shaders/texture.fs.glsl");

TextureEntity::TextureEntity()
{
	// TODO: generate this from arguments
	TextureVertex vertices[4];
	vertices[0].pos = { 0.5f, 0.5f, 0.0f };
	vertices[0].texPos = { 1.0f, 1.0f };
	vertices[1].pos = { 0.5f, -0.5f, 0.0f };
	vertices[1].texPos = { 1.0f, 0.0f };
	vertices[2].pos = { 0.0f, -0.5f, 0.0f };
	vertices[2].texPos = { 0.0f, 0.0f };
	vertices[3].pos = { 0.0f, 0.5f, 0.0f };
	vertices[3].texPos = { 0.0f, 1.0f };

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

TextureEntity::~TextureEntity()
{
	glDeleteVertexArrays(1, &mesh.vao);
	glDeleteBuffers(1, &mesh.vbo);
	glDeleteBuffers(1, &mesh.ebo);
}

bool TextureEntity::init(const char* path)
{
	if (!shader.init(VSShaderPath.c_str(), FSShaderPath.c_str()))
		return false;

	shader.use();
	glUniform1i(glGetUniformLocation(shader.program, "sampler0"), 0);
	
	return texture.init(path);
}

void TextureEntity::draw()
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(TextureVertex), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(TextureVertex), (void*)sizeof(Vec3));

	/* Draw triangles */
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
