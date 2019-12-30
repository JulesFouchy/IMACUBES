#pragma once

#include "BoundingBoxIterator.hpp"

class BoundingBox {
friend class BoundingBoxIterator;
public:
	BoundingBox(); 
	~BoundingBox() = default;

	BoundingBoxIterator begin();
	BoundingBoxIterator end();

	bool isXValid(int x) const;
	bool isYValid(int y) const;
	bool isZValid(int z) const;
	bool isCubeInside(const glm::ivec3& pos) const;

private:
	int m_minValidX;
	int m_maxValidX;
	int m_minValidY;
	int m_maxValidY;
	int m_minValidZ;
	int m_maxValidZ;
};