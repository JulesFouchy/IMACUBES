#include "Tool_Cube.hpp"

#include "Helper/Maths.hpp"
#include <algorithm>

#include "CubesMap/BoundingBox.hpp"

#include "UI/Input.hpp"

Tool_Cube::Tool_Cube()
	: Tool_Shape(),
	m_radiuses(5)
{
}

void Tool_Cube::applyOnShape(std::function<void(const glm::ivec3 & pos)> whatToDoWithPos) {
	BoundingBox bbox(m_center, m_radiuses, CENTER);
	for (const glm::ivec3& pos : bbox) {
		whatToDoWithPos(pos);
	}
}

void Tool_Cube::onWheelScroll(int dl) {
	if (Input::KeyIsDown('x'))
		m_radiuses.x = std::max(m_radiuses.x + dl, 0);
	else if (Input::KeyIsDown('c'))
		m_radiuses.z = std::max(m_radiuses.z + dl, 0);
	else if (Input::KeyIsDown('v'))
		m_radiuses.y = std::max(m_radiuses.y + dl, 0);
	else {
		m_radiuses.x = std::max(m_radiuses.x + dl, 0);
		m_radiuses.y = std::max(m_radiuses.y + dl, 0);
		m_radiuses.z = std::max(m_radiuses.z + dl, 0);
	}
}

void Tool_Cube::update(const Cursor& cursor) {
	m_center = cursor.getCubeJustBeforePosition();
	computePreview();
	if (Input::KeyIsDown(SPACE))
		replaceMaterials();
}