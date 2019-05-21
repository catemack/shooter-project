#pragma once

// stdlib
#include <string>

#include <utils/shader.hpp>
#include <common.hpp>

class Renderable
{
public:
	virtual ~Renderable();

	virtual void draw() = 0;

protected:
	Shader shader;
	Mesh mesh;
};
