#include "Tool_Cube.hpp"

#include "Helper/Maths.hpp"
#include <algorithm>

#include "CubesMap/BoundingBox.hpp"

Tool_Cube::Tool_Cube()
	: Tool_Shape(),
	m_center(0.0f), m_radius(1.0f)
{
}

void Tool_Cube::applyOnShape(std::function<void(const glm::ivec3 & pos)> whatToDoWithPos) {
	BoundingBox bbox(m_center, m_radius);
	for (const glm::ivec3& pos : bbox) {
		whatToDoWithPos(pos);
	}
}

void Tool_Cube::onWheelScroll(int dl) {
	m_radius = std::max(m_radius + dl, 0);
}

void Tool_Cube::update(const Cursor& cursor) {
	m_center = cursor.getCubeJustBeforePosition();
	computePreview();
}