#include "camera.hpp"

Camera::Camera() :
	pitch(0.0f),
	yaw(-90.0f),
	pos(glm::vec3(0.0f, 0.0f, 3.0f)),
	front(glm::vec3(0.0f, 0.0f, -1.0f)),
	up(glm::vec3(0.0f, 1.0f, 0.0f))
{
}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(pos, pos + front, up);
}
