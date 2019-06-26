#pragma once

#include <common.hpp>

class Camera
{
public:
	Camera(const glm::vec3 position);

	glm::mat4 getViewMatrix() const;
	glm::vec3 getPos() const;

	void move(float forward, float right);
	void tilt(float deltaYaw, float deltaPitch);

private:
	float pitch;
	float yaw;

	glm::vec3 pos;
	glm::vec3 front;
	glm::vec3 up;
};
