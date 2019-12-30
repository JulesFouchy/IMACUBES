#include "BoundingBox.hpp"

#include "Locator/Locate.hpp"
#include "CubesMap/CubesMap.hpp"

BoundingBox::BoundingBox()
	: m_minValidX(Locate::cubesMap().minValidX()), m_maxValidX(Locate::cubesMap().maxValidX()),
	  m_minValidY(Locate::cubesMap().minValidY()), m_maxValidY(Locate::cubesMap().maxValidY()),
	  m_minValidZ(Locate::cubesMap().minValidZ()), m_maxValidZ(Locate::cubesMap().maxValidZ())
{}

BoundingBoxIterator BoundingBox::begin() {
	return BoundingBoxIterator(*this);
}
BoundingBoxIterator BoundingBox::end() {
	BoundingBoxIterator it(*this);
	it.m_pos = glm::ivec3(m_minValidX, m_minValidY, m_maxValidZ + 1);
	return it;
}

bool BoundingBox::isXValid(int x) const {
	return x >= m_minValidX && x <= m_maxValidX;
}
bool BoundingBox::isYValid(int y) const {
	return y >= m_minValidY && y <= m_maxValidY;
}
bool BoundingBox::isZValid(int z) const {
	return z >= m_minValidZ && z <= m_maxValidZ;
}
bool BoundingBox::isCubeInside(const glm::ivec3& pos) const {
	return isXValid(pos.x) && isYValid(pos.y) && isZValid(pos.z);
}