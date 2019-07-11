#pragma once

#include <array>

#include <common.hpp>
#include "renderable.hpp"
#include "collidable.hpp"
#include "player.hpp"

class Wall : public Collidable, public Renderable
{
public:
	Wall(glm::vec3 position, glm::vec4 color, std::array<std::array<glm::vec3, 4>, 6> wallBounds);

	bool collidesWith(const Player& player);

	virtual void draw(const Camera& camera);
	virtual void draw(const Camera& camera, const glm::vec3 lightColor, const float lightIntensity);
};
