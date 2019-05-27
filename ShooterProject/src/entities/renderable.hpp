#pragma once

// stdlib
#include <string>

#include <utils/shader.hpp>
#include <utils/camera.hpp>
#include <common.hpp>

class Renderable
{
public:
	virtual ~Renderable();

	virtual void draw(const Camera& camera) = 0;

	glm::vec3 pos;

protected:
	Shader shader;
	Mesh mesh;
};
