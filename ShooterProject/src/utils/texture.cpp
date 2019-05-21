#include <utils/texture.hpp>

// stb
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture() :
	id(0),
	height(0),
	width(0)
{
}

Texture::~Texture()
{
	if (id != 0) glDeleteTextures(1, &id);
}

bool Texture::init(const char* image)
{
	// Load image file using stb
	stbi_set_flip_vertically_on_load(true);
	stbi_uc* data = stbi_load(image, &width, &height, NULL, 4);

	if (data == NULL)
	{
		//fprintf("Failed to load texture %s", image);
		std::cout << "Failed to load texture " << image << std::endl;
		stbi_image_free(data);
		return false;
	}

	// Initialize and bind the texture
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	// Set texture wrapping/filtering options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Generate texture from image file
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Free image memory
	stbi_image_free(data);

	return true;
}
