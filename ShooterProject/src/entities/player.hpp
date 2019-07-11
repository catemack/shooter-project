#pragma once

#include <common.hpp>
#include "collidable.hpp"
#include <utils/camera.hpp>

class Player : public Collidable
{
public:
	Player(glm::vec3 position);

	void move(float deltaTimeForward, float deltaTimeRight);
	void look(float deltaX, float deltaY);
	glm::vec3 getPos();
	const Camera getCamera();

private:
	Camera camera;
	const float speed = 2.5f;
	const float lookSensitivity = 0.05f;
};
