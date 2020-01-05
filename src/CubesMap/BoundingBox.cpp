#include "BoundingBox.hpp"

#include "Locator/Locate.hpp"
#include "CubesMap/CubesMap.hpp"

#include "Helper/Maths.hpp"

BoundingBox::BoundingBox()
	: m_minValidX(Locate::cubesMap().minValidX()), m_maxValidX(Locate::cubesMap().maxValidX()),
	  m_minValidY(Locate::cubesMap().minValidY()), m_maxValidY(Locate::cubesMap().maxValidY()),
	  m_minValidZ(Locate::cubesMap().minValidZ()), m_maxValidZ(Locate::cubesMap().maxValidZ())
{}

BoundingBox::BoundingBox(const glm::ivec3& center, int radius)
	: m_minValidX(clampX(center.x - radius)), m_maxValidX(clampX(center.x + radius)),
	  m_minValidY(clampY(center.y - radius)), m_maxValidY(clampY(center.y + radius)),
	  m_minValidZ(clampZ(center.z - radius)), m_maxValidZ(clampZ(center.z + radius))
{

}

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

int BoundingBox::clampX(int x){
	return MyMaths::Clamp(x, Locate::cubesMap().minValidX(), Locate::cubesMap().maxValidX());
}

int BoundingBox::clampY(int y){
	return MyMaths::Clamp(y, Locate::cubesMap().minValidY(), Locate::cubesMap().maxValidY());
}

int BoundingBox::clampZ(int z) {
	return MyMaths::Clamp(z, Locate::cubesMap().minValidZ(), Locate::cubesMap().maxValidZ());
}
