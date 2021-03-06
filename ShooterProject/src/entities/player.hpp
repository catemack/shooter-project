#pragma once

#include <common.hpp>
#include "collidable.hpp"
#include <utils/camera.hpp>
#include "wall.hpp"
#include "bullet.hpp"

class Player : public Collidable
{
public:
	Player(glm::vec3 position);

	void move(glm::vec3 delta);
	void move(float deltaTimeForward, float deltaTimeRight);
	void look(float deltaX, float deltaY);
	glm::vec3 getPos();
	const Camera getCamera();
	std::unique_ptr<Bullet> fire();

	void resolveCollision(const Wall& wall);

private:
	Camera camera;
	const float speed = 2.5f;
	const float lookSensitivity = 0.05f;
	const float bulletSpeed = 50.0f;
};
