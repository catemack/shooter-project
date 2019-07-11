#include "player.hpp"

std::array<std::array<glm::vec3, 4>, 6> playerBounds{ {
	{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, -0.5f) },
	{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, 0.5f) },
	{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(-0.5f, -0.5f, 0.5f) },
	{ glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, 0.5f) },
	{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, -0.5f, 0.5f) },
	{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, -0.5f, 0.5f) }
} };

Player::Player(glm::vec3 position) :
	Collidable(position, playerBounds),
	camera(position)
{
}

void Player::move(float deltaTimeForward, float deltaTimeRight)
{
	// Get the normalized projection of the player's direction on the XZ axis from the camera's facing
	// Keeps player bound to horizontal movement
	glm::vec3 frontProj = glm::vec3(camera.getFront().x, 0.0f, camera.getFront().z);
	frontProj = glm::normalize(frontProj);
	glm::vec3 delta = (deltaTimeForward * frontProj + deltaTimeRight * glm::normalize(glm::cross(frontProj, camera.getUp()))) * speed;

	Collidable::displace(delta);
	camera.displace(delta);
}

void Player::look(float deltaX, float deltaY)
{
	// TODO: uncomment this when rotating bounding box fixed
	//Collidable::rotateRadians(deltaX * lookSensitivity);
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
