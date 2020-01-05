#include "Tool_Sphere.hpp"

#include "Locator/Locate.hpp"
#include "CubesMap/CubesMap.hpp"
#include "CubesMap/BoundingBox.hpp"
#include "History/History.hpp"

#include "Helper/Maths.hpp"

Tool_Sphere::Tool_Sphere()
	: Tool(),
	  m_bCenterSelected(false),
	  m_center(0.0f), m_radius(5.0f)
{
}

void Tool_Sphere::onLeftClicDown(const Cursor& cursor) {
	if (!m_bCenterSelected) {
		m_center = cursor.getPosition();
		m_bCenterSelected = true;
	}
	else {
		generateSphere();
	}
}

void Tool_Sphere::generateSphere() {
	History& history = Locate::history(HistoryType::Cubes);
	BoundingBox bbox(m_center, m_radius);
	history.beginUndoGroup();
	for (const glm::ivec3& pos : bbox) {
		Locate::cubesMap().addCube(pos);
	}
	history.endUndoGroup();
}