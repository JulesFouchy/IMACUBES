#include "Tool_Sphere.hpp"

#include "Helper/Maths.hpp"
#include <algorithm>

#include "CubesMap/BoundingBox.hpp"

Tool_Sphere::Tool_Sphere()
	: Tool_Shape(),
	  m_radius(5.0f)
{
}

void Tool_Sphere::applyOnShape(std::function<void(const glm::ivec3 & pos)> whatToDoWithPos) {
	BoundingBox bbox(m_center, m_radius);
	for (const glm::ivec3& pos : bbox) {
		if (glm::length((const glm::vec3)(pos - m_center)) <= m_radius)
			whatToDoWithPos(pos);
	}
}

void Tool_Sphere::onWheelScroll(int dl) {
	m_radius = std::max(m_radius + dl, 0);
}

void Tool_Sphere::update(const Cursor& cursor) {
	m_center = cursor.getCubeJustBeforePosition();
	computePreview();
}