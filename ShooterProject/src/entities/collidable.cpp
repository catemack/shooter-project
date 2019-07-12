#include "collidable.hpp"
#include "glm/gtx/string_cast.hpp"

Collidable::Collidable(glm::vec3 position, std::array<std::array<glm::vec3, 4>, 6> box) :
	pos(position),
	realArea(box)
{
	displace(pos);
	boundingBox = { {{glm::vec3(0.0f)}} };
	updateBoundingBox();
}

void Collidable::displace(glm::vec3 delta)
{
	pos += delta;

	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			realArea[i][j] += delta;
			boundingBox[i][j] += delta;
		}
	}
}

void Collidable::displace(float x, float y, float z)
{
	displace(glm::vec3(x, y, z));
}

void Collidable::rotateDegrees(float r)
{
	rotateRadians(r * glm::pi<float>() / 180.0f);
}

void Collidable::rotateRadians(float r)
{
	float cosR = cos(r);
	float sinR = sin(r);

	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			glm::vec3 p = realArea[i][j] - pos;

			float newX = p.x * cosR - p.z * sinR;
			float newZ = p.x * sinR + p.z * cosR;

			realArea[i][j] = glm::vec3(newX + pos.x, realArea[i][j].y, newZ + pos.z);
		}
	}

	updateBoundingBox();
}

const glm::vec3 Collidable::getPos() const
{
	return pos;
}

const std::array<std::array<glm::vec3, 4>, 6>& Collidable::getBounds() const
{
	return boundingBox;
}

bool Collidable::intersects(const Collidable& other)
{
	std::array<std::array<glm::vec3, 4>, 6> otherBounds = other.getBounds();

	return boundingBox[0][0].x <= otherBounds[0][2].x && boundingBox[0][2].x >= otherBounds[0][0].x &&
		boundingBox[0][0].y <= otherBounds[0][1].y && boundingBox[0][1].y >= otherBounds[0][0].y &&
		boundingBox[1][0].z <= otherBounds[0][0].z && boundingBox[0][0].z >= otherBounds[1][0].z;
}

void Collidable::updateBoundingBox()
{
	// Get the bounds of the actual area of the object
	float minX = INFINITY;
	float maxX = -INFINITY;
	float minY = INFINITY;
	float maxY = -INFINITY;
	float minZ = INFINITY;
	float maxZ = -INFINITY;

	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (realArea[i][j].x < minX)
				minX = realArea[i][j].x;
			if (realArea[i][j].x > maxX)
				maxX = realArea[i][j].x;
			if (realArea[i][j].y < minY)
				minY = realArea[i][j].y;
			if (realArea[i][j].y > maxY)
				maxY = realArea[i][j].y;
			if (realArea[i][j].z < minZ)
				minZ = realArea[i][j].z;
			if (realArea[i][j].z > maxZ)
				maxZ = realArea[i][j].z;
		}
	}

	// top
	boundingBox[0][0] = glm::vec3(minX, minY, maxZ);
	boundingBox[0][1] = glm::vec3(minX, maxY, maxZ);
	boundingBox[0][2] = glm::vec3(maxX, maxY, maxZ);
	boundingBox[0][3] = glm::vec3(maxX, minY, maxZ);

	// bottom
	boundingBox[1][0] = glm::vec3(minX, minY, minZ);
	boundingBox[1][1] = glm::vec3(minX, maxY, minZ);
	boundingBox[1][2] = glm::vec3(maxX, maxY, minZ);
	boundingBox[1][3] = glm::vec3(maxX, minY, minZ);

	// front
	boundingBox[2][0] = glm::vec3(minX, minY, minZ);
	boundingBox[2][1] = glm::vec3(minX, minY, maxZ);
	boundingBox[2][2] = glm::vec3(maxX, minY, maxZ);
	boundingBox[2][3] = glm::vec3(maxX, minY, minZ);

	// back
	boundingBox[3][0] = glm::vec3(minX, maxY, minZ);
	boundingBox[3][1] = glm::vec3(minX, maxY, maxZ);
	boundingBox[3][2] = glm::vec3(maxX, maxY, maxZ);
	boundingBox[3][3] = glm::vec3(maxX, maxY, minZ);

	// left
	boundingBox[4][0] = glm::vec3(minX, minY, minZ);
	boundingBox[4][1] = glm::vec3(minX, minY, maxZ);
	boundingBox[4][2] = glm::vec3(minX, maxY, maxZ);
	boundingBox[4][3] = glm::vec3(minX, maxY, minZ);

	// right
	boundingBox[5][0] = glm::vec3(maxX, minY, minZ);
	boundingBox[5][1] = glm::vec3(maxX, minY, maxZ);
	boundingBox[5][2] = glm::vec3(maxX, maxY, maxZ);
	boundingBox[5][3] = glm::vec3(maxX, maxY, minZ);
}
