#pragma once

#include "renderable.hpp"

class ColorEntity : public Renderable
{
public:
	ColorEntity();
	virtual ~ColorEntity();

	bool init();
	virtual void draw();

private:
	static const std::string VSShaderPath;
	static const std::string FSShaderPath;
};
