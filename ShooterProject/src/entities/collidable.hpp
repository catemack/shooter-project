#pragma once

#include <common.hpp>

class Collidable
{
public:
	//Collidable(glm::vec3 position, glm::vec3 box[6][4]);
	Collidable(glm::vec3 position, std::array<std::array<glm::vec3, 4>, 6> box);

	const glm::vec3 getPos() const;
	const std::array<std::array<glm::vec3, 4>, 6>& getBounds() const;
	void displace(glm::vec3 delta);
	void displace(float x, float y, float z);
	void rotateDegrees(float r);
	void rotateRadians(float r);
	bool intersects(const Collidable& other);

private:
	glm::vec3 pos;
	std::array<std::array<glm::vec3, 4>, 6> realArea;
	//glm::vec3 realArea[6][4];
	std::array<std::array<glm::vec3, 4>, 6> boundingBox;
	//glm::vec3 boundingBox[6][4];

	void updateBoundingBox();
};
