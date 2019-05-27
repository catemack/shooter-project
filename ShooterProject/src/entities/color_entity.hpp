#pragma once

#include "renderable.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>

class ColorEntity : public Renderable
{
public:
	ColorEntity(glm::vec3 position, ColorVertex vertices[], GLuint triangles[], int size);
	virtual ~ColorEntity();

	bool init();
	virtual void draw(const Camera& camera);

private:
	static const std::string VSShaderPath;
	static const std::string FSShaderPath;
};
