#include "CubesMap.hpp"

CubesMap::CubesMap(size_t width, size_t height, size_t depth)
	: m_width(width), m_height(height), m_depth(depth), m_cubesLocations(m_width * m_height * m_depth, MaterialLocation(-1, -1))
{

}

void CubesMap::addCube(glm::ivec3 id3D) {
	const MaterialLocation& currentMatLoc = getMaterialLocationOf(id3D);
	if (currentMatLoc.isValid())
		m_materialsManager.removeCube(currentMatLoc.shaderID, id3D);
	MaterialLocation& newMatLoc = m_materialsManager.addCube(id3D);
	setMaterialLocation(id3D, newMatLoc);	
}

size_t CubesMap::index1Dfrom3D(glm::ivec3 id3D) const {
	return id3D.x + id3D.y * m_width + id3D.y * m_width * m_height;
}