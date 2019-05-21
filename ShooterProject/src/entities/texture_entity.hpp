#pragma once

#include "renderable.hpp"

#include <utils/texture.hpp>

class TextureEntity : public Renderable
{
public:
	TextureEntity();
	virtual ~TextureEntity();

	bool init(const char* path);
	virtual void draw();

private:
	static const std::string VSShaderPath;
	static const std::string FSShaderPath;

	Texture texture;
};
