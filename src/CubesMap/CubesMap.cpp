#include "CubesMap.hpp"

#include "Locator/Locate.hpp"

CubesMap::CubesMap(size_t width, size_t height, size_t depth)
	: m_width(width), m_height(height), m_depth(depth), m_cubesLocations(m_width * m_height * m_depth, MaterialLocation(-1, -1))
{

}

void CubesMap::addCube(glm::ivec3 id3D, bool bPushActionInHistory) {
	// Dont forget to call history.beginUndoGroup() if you want to push the action in history !
	const MaterialLocation& currentMatLoc = getMaterialLocationOf(id3D);
	if (currentMatLoc.isValid())
		m_materialsManager.removeCube(currentMatLoc.shaderID, id3D, bPushActionInHistory);
	MaterialLocation& newMatLoc = m_materialsManager.addCube(id3D, bPushActionInHistory);
	setMaterialLocation(id3D, newMatLoc, bPushActionInHistory);
}

void CubesMap::removeCube(glm::ivec3 id3D, bool bPushActionInHistory) {
	const MaterialLocation& currentMatLoc = getMaterialLocationOf(id3D);
	if (currentMatLoc.isValid())
		m_materialsManager.removeCube(currentMatLoc.shaderID, id3D, bPushActionInHistory);
	setMaterialLocation(id3D, MaterialLocation(-1,-1), bPushActionInHistory);
}

size_t CubesMap::index1Dfrom3D(glm::ivec3 id3D) const {
	assert(isIDvalid(id3D));
	return id3D.x + id3D.y * m_width + id3D.z * m_width * m_height;
}

bool CubesMap::isIDvalid(glm::ivec3 id3D) const {
	return id3D.x > -1 && id3D.x < m_width && id3D.y>-1 && id3D.y < m_height && id3D.z>-1 && id3D.z < m_depth;
}

void CubesMap::setMaterialLocation(glm::ivec3 id3D, const MaterialLocation& matLoc, bool bPushActionInHistory){
	if (bPushActionInHistory) {
		MaterialLocation prevLoc = m_cubesLocations[index1Dfrom3D(id3D)];
		MaterialLocation newLoc = matLoc;
		Locate::history(HistoryType::Cubes).addAction(Action(
			// DO action
			[this, newLoc, id3D]()
		{
			this->setMaterialLocation(id3D, newLoc, false);
		},
			// UNDO action
			[this, prevLoc, id3D]()
		{
			this->setMaterialLocation(id3D, prevLoc, false);
		}
		));
	}
	m_cubesLocations[index1Dfrom3D(id3D)] = matLoc;
}