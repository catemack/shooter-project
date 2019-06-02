#include "renderable.hpp"

Renderable::Renderable(const std::string& vsPath, const std::string& fsPath) :
	shader(vsShaderPath(vsPath), fsShaderPath(fsPath)),
	mesh()
{
	/* Set up vertex array object, vertex buffer */
	glGenVertexArrays(1, &mesh.vao);
	glGenBuffers(1, &mesh.vbo);
}

Renderable::~Renderable()
{
	glDeleteVertexArrays(1, &mesh.vao);
	glDeleteBuffers(1, &mesh.vbo);
}

std::string Renderable::vsShaderPath(std::string name)
{
	return std::string("./shaders/") + name + std::string(".vs.glsl");
}

std::string Renderable::fsShaderPath(std::string name)
{
	return std::string("./shaders/") + name + std::string(".fs.glsl");
}
