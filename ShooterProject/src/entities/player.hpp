#pragma once

#include <common.hpp>
#include "collidable.hpp"
#include <utils/camera.hpp>
#include "wall.hpp"

class Player : public Collidable
{
public:
	Player(glm::vec3 position);

	void move(glm::vec3 delta);
	void move(float deltaTimeForward, float deltaTimeRight);
	void look(float deltaX, float deltaY);
	glm::vec3 getPos();
	const Camera getCamera();

	void resolveCollision(const Wall& wall);

private:
	Camera camera;
	const float speed = 2.5f;
	const float lookSensitivity = 0.05f;
};
