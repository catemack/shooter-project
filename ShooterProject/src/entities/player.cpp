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

void Player::move(glm::vec3 delta)
{
	Collidable::displace(delta);
	camera.displace(delta);
}

void Player::move(float deltaTimeForward, float deltaTimeRight)
{
	// Get the normalized projection of the player's direction on the XZ axis from the camera's facing
	// Keeps player bound to horizontal movement
	glm::vec3 frontProj = glm::vec3(camera.getFront().x, 0.0f, camera.getFront().z);
	frontProj = glm::normalize(frontProj);
	glm::vec3 delta = (deltaTimeForward * frontProj + deltaTimeRight * glm::normalize(glm::cross(frontProj, camera.getUp()))) * speed;

	move(delta);
}

void Player::look(float deltaX, float deltaY)
{
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

std::unique_ptr<Bullet> Player::fire()
{
	return std::make_unique<Bullet>(getPos(), camera.getFront() * bulletSpeed);
}

// TODO: consider a force-based resolution mechanism (once player acceleration is a thing)
void Player::resolveCollision(const Wall& wall)
{
	std::array<std::array<glm::vec3, 4>, 6> wallBounds = wall.getBounds();
	float minX = wallBounds[0][0].x;
	float maxX = wallBounds[5][0].x;
	float minZ = wallBounds[1][0].z;
	float maxZ = wallBounds[0][0].z;

	float delta = getPos().x - minX;
	glm::vec3 displacement = glm::vec3(-delta - (0.5*std::sqrt(2)), 0.0, 0.0);

	if (maxX - getPos().x < delta)
	{
		delta = maxX - getPos().x;
		displacement = glm::vec3(delta + (0.5 * std::sqrt(2)), 0.0, 0.0);
	}
	if (getPos().z - minZ < delta)
	{
		delta = getPos().z - minZ;
		displacement = glm::vec3(0.0, 0.0, -delta - (0.5 * std::sqrt(2)));
	}
	if (maxZ - getPos().z < delta)
	{
		delta = maxZ - getPos().z;
		displacement = glm::vec3(0.0, 0.0, delta + (0.5 * std::sqrt(2)));
	}

	move(displacement);
}
