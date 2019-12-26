#include "CubesMap.hpp"

#include "Locator/Locate.hpp"

CubesMap::CubesMap(int width, int height, int depth)
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

bool CubesMap::isPositionInsideWorld(const glm::vec3& pos) { 
	return pos.x > minX() - 0.5f && pos.x < maxX() + 0.5f && pos.y > minY() - 0.5f && pos.y < maxY() + 0.5f && pos.z > minZ() - 0.5f && pos.z < maxZ() + 0.5f;
}

int CubesMap::minX() const{
	return -m_width / 2;
}
int CubesMap::maxX() const{
	return m_width - m_width / 2 - 1;
}
int CubesMap::minY() const{
	return -m_height / 2;
}
int CubesMap::maxY() const {
	return m_height - m_height / 2 - 1;
}
int CubesMap::minZ() const {
	return -m_depth/ 2;
}
int CubesMap::maxZ() const {
	return m_depth - m_depth / 2 - 1;
}

int CubesMap::index1Dfrom3D(glm::ivec3 id3D) const {
	assert(isID3Dvalid(id3D));
	return (id3D.x+m_width/2) + (id3D.y+m_height/2) * m_width + (id3D.z+m_depth/2) * m_width * m_height;
}

bool CubesMap::isID3Dvalid(glm::ivec3 id3D) const {
	return id3D.x >= minX() && id3D.x <= maxX()  && id3D.y>= minY() && id3D.y <= maxY() && id3D.z>= minZ() && id3D.z <= maxZ();
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