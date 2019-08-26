#pragma once

#include <common.hpp>
#include "renderable.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>

class ColorEntity : public Renderable
{
public:
	ColorEntity(const glm::vec3 position, const std::vector<ColorVertex> vertices, const std::string vsShader, const std::string fsShader);
	virtual void draw(const Camera& camera);
	virtual void draw(const Camera& camera, const glm::vec3 lightColor, const float lightIntensity);

private:
	void setVertexArrays(const std::vector<ColorVertex> vertices);
	void setVertexArrays(const ColorVertex vertices[], const int size);
};
