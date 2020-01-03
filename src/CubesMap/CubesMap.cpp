#include "CubesMap.hpp"

#include "Locator/Locate.hpp"
#include "History/History.hpp"

CubesMap::CubesMap(int width, int height, int depth)
	: m_width(width), m_height(height), m_depth(depth), m_cubesLocations(m_width * m_height * m_depth, MaterialLocation(-1, -1))
{

}

void CubesMap::addCube(const glm::ivec3& id3D, bool bPushActionInHistory) {
	// Dont forget to call history.beginUndoGroup() if you want to push the action in history !
	const MaterialLocation& currentMatLoc = (*this)[id3D];
	if (currentMatLoc.isValid())
		m_materialsManager.removeCube(currentMatLoc.shaderID, id3D, bPushActionInHistory);
	MaterialLocation& newMatLoc = m_materialsManager.addCube(id3D, bPushActionInHistory);
	setMaterialLocation(id3D, newMatLoc, bPushActionInHistory);
}

void CubesMap::removeCube(const glm::ivec3& id3D, bool bPushActionInHistory) {
	const MaterialLocation& currentMatLoc = (*this)[id3D];
	if (currentMatLoc.isValid())
		m_materialsManager.removeCube(currentMatLoc.shaderID, id3D, bPushActionInHistory);
	setMaterialLocation(id3D, MaterialLocation(-1,-1), bPushActionInHistory);
}

int CubesMap::index1Dfrom3D(const glm::ivec3& id3D) const {
	assert(isID3Dvalid(id3D));
	return (id3D.x+m_width/2) + (id3D.y+m_height/2) * m_width + (id3D.z+m_depth/2) * m_width * m_height;
}

bool CubesMap::isID3Dvalid(const glm::ivec3& id3D) const {
	return id3D.x >= minValidX() && id3D.x <= maxValidX()  && id3D.y>= minValidY() && id3D.y <= maxValidY() && id3D.z>= minValidZ() && id3D.z <= maxValidZ();
}

bool CubesMap::isPositionInsideWorld(const glm::vec3& pos) const {
	return pos.x > minValidX() - 0.5f && pos.x < maxValidX() + 0.5f && pos.y > minValidY() - 0.5f && pos.y < maxValidY() + 0.5f && pos.z > minValidZ() - 0.5f && pos.z < maxValidZ() + 0.5f;
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