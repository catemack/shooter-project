#pragma once

#include <array>

#include <common.hpp>
#include "renderable.hpp"
#include "collidable.hpp"
#include "wall.hpp"

class Bullet : public Collidable, public Renderable
{
public:
	Bullet(const glm::vec3 position, const glm::vec3 velocity);
	Bullet(const Bullet& b) : Bullet(b.getPos(), b.getVelocity()) {};

	virtual void draw(const Camera& camera);
	virtual void draw(const Camera&, const glm::vec3 lightColor, const float lightIntensity);

	void move(float deltaTime);
	void resolveCollision(const Wall& wall);
	bool shouldCleanUp();
	bool outOfBounds();
	const glm::vec3 getVelocity() const;

private:
	glm::vec3 v;
	bool toBeDestroyed;
};
