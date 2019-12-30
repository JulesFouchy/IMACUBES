#include "BoundingBoxIterator.hpp"
#include "BoundingBox.hpp"

BoundingBoxIterator::BoundingBoxIterator(const BoundingBox& boundingBox)
	: m_pos(glm::ivec3(boundingBox.m_minValidX, boundingBox.m_minValidY, boundingBox.m_minValidZ)),
	  m_boundingBox(boundingBox)
{}

const glm::ivec3& BoundingBoxIterator::operator*() {
	return m_pos;
}

void BoundingBoxIterator::operator++() {
	// increase X
	if (m_pos.x < m_boundingBox.m_maxValidX)
		m_pos.x++;
	// carry X
	else {
		m_pos.x = m_boundingBox.m_minValidX;
		m_pos.y++;
	}
	// carry Y
	if (m_pos.y > m_boundingBox.m_maxValidY) {
		m_pos.y = m_boundingBox.m_minValidY;
		m_pos.z++;
	}
	// first invalid position is : (minX, minY, maxZ+1)
}

bool BoundingBoxIterator::operator!=(BoundingBoxIterator& it) {
	return m_pos != it.m_pos;
}