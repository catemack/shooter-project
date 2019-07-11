#pragma once

#include <common.hpp>

class Camera
{
public:
	Camera(const glm::vec3 position);

	const glm::mat4 getViewMatrix() const;
	const glm::vec3 getPos() const;
	const glm::vec3 getFront() const;
	const glm::vec3 getUp() const;

	void displace(glm::vec3 delta);
	void tilt(float deltaYaw, float deltaPitch);

private:
	float pitch;
	float yaw;

	glm::vec3 pos;
	glm::vec3 front;
	glm::vec3 up;
};
