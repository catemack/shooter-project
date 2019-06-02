#pragma once

// stdlib
#include <string>

#include <utils/shader.hpp>
#include <utils/camera.hpp>
#include <common.hpp>

class Renderable
{
public:
	Renderable(const std::string& vsPath, const std::string& fsPath);
	virtual ~Renderable();

	virtual void draw(const Camera& camera) = 0;
	virtual void draw(const Camera& camera, const glm::vec3 lightColor, const float lightIntensity) = 0;

	glm::vec3 pos;

protected:
	static std::string vsShaderPath(std::string name);
	static std::string fsShaderPath(std::string name);

	Shader shader;
	Mesh mesh;
};
