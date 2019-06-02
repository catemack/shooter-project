#pragma once

#include "renderable.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>

class ColorEntity : public Renderable
{
public:
	ColorEntity(const glm::vec3 position, const ColorVertex vertices[], const int size, const std::string vsShader, const std::string fsShader);
	ColorEntity(glm::vec3 position, ColorVertex vertices[], const int size);
	ColorEntity(glm::vec3 position, glm::vec4 color, glm::vec3 vertices[], const int size, const std::string vsShader, const std::string fsShader);

	virtual void draw(const Camera& camera);
	virtual void draw(const Camera& camera, const glm::vec3 lightColor, const float lightIntensity);

private:
	void init(const glm::vec3 position, const ColorVertex vertices[], const int size, const std::string vsShader, const std::string fsShader);
	void setVertexArrays(const ColorVertex vertices[], const int size);

	static const std::string VSShaderPath;
	static const std::string FSShaderPath;
};
