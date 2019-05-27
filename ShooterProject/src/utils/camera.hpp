#pragma once

#include <common.hpp>

class Camera
{
public:
	Camera();

	glm::mat4 getViewMatrix() const;

	float pitch;
	float yaw;

	glm::vec3 pos;
	glm::vec3 front;
	glm::vec3 up;
};
