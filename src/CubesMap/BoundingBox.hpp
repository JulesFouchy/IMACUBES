#pragma once

#include "BoundingBoxIterator.hpp"

enum BboxGenerationMode {
	CENTER,
	CORNERS
};

class BoundingBox {
friend class BoundingBoxIterator;
public:
	BoundingBox(); 
	BoundingBox(const glm::ivec3& v0, const glm::ivec3& v1, BboxGenerationMode mode);
	~BoundingBox() = default;

	BoundingBoxIterator begin();
	BoundingBoxIterator end();

	bool isXValid(int x) const;
	bool isYValid(int y) const;
	bool isZValid(int z) const;
	bool isCubeInside(const glm::ivec3& pos) const;

	inline const glm::ivec3& size() { return m_size; }
	inline const glm::ivec3& center() { return m_center; }

private:
	void computeInfos();

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

	glm::ivec3 m_size;
	glm::ivec3 m_center;
};