#include "BoundingBox.hpp"

#include "Locator/Locate.hpp"
#include "CubesMap/CubesMap.hpp"

#include "Helper/Maths.hpp"

BoundingBox::BoundingBox()
	: m_minValidX(Locate::cubesMap().minValidX()), m_maxValidX(Locate::cubesMap().maxValidX()),
	  m_minValidY(Locate::cubesMap().minValidY()), m_maxValidY(Locate::cubesMap().maxValidY()),
	  m_minValidZ(Locate::cubesMap().minValidZ()), m_maxValidZ(Locate::cubesMap().maxValidZ())
{
	computeInfos();
}

BoundingBox::BoundingBox(const glm::ivec3& v0, const glm::ivec3& v1, BboxGenerationMode mode) {
	switch (mode)
	{
	case CENTER:
		// v0 = center
		// v1 = radiuses
		m_minValidX = clampX(v0.x - v1.x); m_maxValidX = clampX(v0.x + v1.x);
		m_minValidY = clampX(v0.y - v1.y); m_maxValidY = clampX(v0.y + v1.y);
		m_minValidZ = clampX(v0.z - v1.z); m_maxValidZ = clampX(v0.z + v1.z);
		break;
	case CORNERS:
		// v0 = corner0
		// v1 = corner1
		m_minValidX = std::min(v0.x, v1.x); m_maxValidX = std::max(v0.x, v1.x);
		m_minValidY = std::min(v0.y, v1.y); m_maxValidY = std::max(v0.y, v1.y);
		m_minValidZ = std::min(v0.z, v1.z); m_maxValidZ = std::max(v0.z, v1.z);
		break;
	default:
		break;
	}
	computeInfos();
}

void BoundingBox::computeInfos() {
	m_size = glm::ivec3(m_maxValidX - m_minValidX,
						m_maxValidY - m_minValidY,
						m_maxValidZ - m_minValidZ
	);
	m_center = glm::ivec3((m_maxValidX + m_minValidX)/2,
						  (m_maxValidY + m_minValidY)/2,
						  (m_maxValidZ + m_minValidZ)/2
	);
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
