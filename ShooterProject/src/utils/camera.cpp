#include "camera.hpp"

Camera::Camera(const glm::vec3 position) :
	pitch(0.0f),
	yaw(-90.0f),
	pos(position),
	front(glm::vec3(0.0f, 0.0f, -1.0f)),
	up(glm::vec3(0.0f, 1.0f, 0.0f))
{
}

void Camera::move(float forward, float right)
{
	// Create a normalized projection of camera.front on the XZ axis
	// Keeps movement limited to horizontal
	glm::vec3 frontProj = glm::vec3(front.x, 0.0f, front.z);
	frontProj = glm::normalize(frontProj);

	pos += forward * frontProj;
	pos += right * glm::normalize(glm::cross(frontProj, up));
}

void Camera::tilt(float deltaYaw, float deltaPitch)
{
	yaw += deltaYaw;
	pitch += deltaPitch;

	// Bind pitch range so camera doesn't do flips
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 newFront;
	newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	newFront.y = sin(glm::radians(pitch));
	newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(newFront);
}

glm::vec3 Camera::getPos() const
{
	return pos;
}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(pos, pos + front, up);
}
