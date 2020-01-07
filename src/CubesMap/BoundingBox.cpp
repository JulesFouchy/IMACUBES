#include "BoundingBox.hpp"

#include "Locator/Locate.hpp"
#include "CubesMap/CubesMap.hpp"

#include "Helper/Maths.hpp"

BoundingBox::BoundingBox()
	: m_minCorner(Locate::cubesMap().minValidX(), 
				  Locate::cubesMap().minValidY(), 
				  Locate::cubesMap().minValidZ()),
	  m_maxCorner(Locate::cubesMap().maxValidX(),
	  			  Locate::cubesMap().maxValidY(),
	  			  Locate::cubesMap().maxValidZ())
{
	computeInfos();
}

BoundingBox::BoundingBox(const glm::ivec3& v0, const glm::ivec3& v1, BboxGenerationMode mode) {
	switch (mode)
	{
	case CENTER:
		// v0 = center
		// v1 = radiuses
		m_minCorner = clamp(v0 - v1);
		m_maxCorner = clamp(v0 + v1);
		break;
	case CENTER_EVENSIZE:
		// v0 = center
		// v1 = radiuses
		m_minCorner = clamp(v0 - v1);
		m_maxCorner = clamp(v0 + v1 - glm::ivec3(1));
		break;
	case CORNERS:
		// v0 = corner0
		// v1 = corner1
		m_minCorner = glm::ivec3(std::min(v0.x, v1.x),
								 std::min(v0.y, v1.y),
								 std::min(v0.z, v1.z)
		);
		m_maxCorner = glm::ivec3 (std::max(v0.x, v1.x),
								  std::max(v0.y, v1.y),
								  std::max(v0.z, v1.z)
		);
		break;
	default:
		break;
	}
	computeInfos();
}

void BoundingBox::computeInfos() {
	m_size = m_maxCorner - m_minCorner;
	m_center = (m_minCorner + m_maxCorner) / 2;
}

BoundingBoxIterator BoundingBox::begin() {
	return BoundingBoxIterator(*this);
}

BoundingBoxIterator BoundingBox::end() {
	BoundingBoxIterator it(*this);
	it.m_pos = glm::ivec3(m_minCorner.x, m_minCorner.y, m_maxCorner.z + 1);
	return it;
}

bool BoundingBox::isXValid(int x) const {
	return x >= m_minCorner.x && x <= m_maxCorner.x;
}
bool BoundingBox::isYValid(int y) const {
	return y >= m_minCorner.y && y <= m_maxCorner.y;
}
bool BoundingBox::isZValid(int z) const {
	return z >= m_minCorner.z && z <= m_maxCorner.z;
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

glm::ivec3 BoundingBox::clamp(const glm::ivec3& v) {
	return glm::ivec3(clampX(v.x), clampY(v.y), clampZ(v.z));
}