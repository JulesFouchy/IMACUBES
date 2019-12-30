#pragma once

#include <glm/glm.hpp>

class BoundingBox;

class BoundingBoxIterator {
friend class BoundingBox;
public:
	BoundingBoxIterator(const BoundingBox& boundingBox);
	~BoundingBoxIterator() = default;

	const glm::ivec3& operator*();
	void operator++();
	bool operator!=(BoundingBoxIterator& it);

private:
	glm::ivec3 m_pos;
	const BoundingBox& m_boundingBox;
};