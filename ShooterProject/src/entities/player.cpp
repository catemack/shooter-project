#include "player.hpp"

Player::Player(glm::vec3 position) :
	camera(position)
{
}

void Player::move(float deltaTimeForward, float deltaTimeRight)
{
	camera.move(deltaTimeForward * speed, deltaTimeRight * speed);
}

void Player::look(float deltaX, float deltaY)
{
	camera.tilt(deltaX * lookSensitivity, deltaY * lookSensitivity);
}

glm::vec3 Player::getPos()
{
	return camera.getPos();
}

const Camera Player::getCamera()
{
	return camera;
}
