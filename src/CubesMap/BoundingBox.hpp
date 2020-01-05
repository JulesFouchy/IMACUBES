#pragma once

#include "BoundingBoxIterator.hpp"

class BoundingBox {
friend class BoundingBoxIterator;
public:
	BoundingBox(); 
	BoundingBox(const glm::ivec3& center, int radius);
	BoundingBox(const glm::ivec3& corner1, const glm::ivec3& corner2);
	~BoundingBox() = default;

	BoundingBoxIterator begin();
	BoundingBoxIterator end();

	bool isXValid(int x) const;
	bool isYValid(int y) const;
	bool isZValid(int z) const;
	bool isCubeInside(const glm::ivec3& pos) const;

private:
	int clampX(int x);
	int clampY(int y);
	int clampZ(int z);

private:
	int m_minValidX;
	int m_maxValidX;
	int m_minValidY;
	int m_maxValidY;
	int m_minValidZ;
	int m_maxValidZ;
};