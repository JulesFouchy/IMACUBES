#include "Tool_Sphere.hpp"

#include "Locator/Locate.hpp"
#include "CubesMap/CubesMap.hpp"
#include "CubesMap/BoundingBox.hpp"
#include "History/History.hpp"

#include "Helper/Maths.hpp"
#include <algorithm>

Tool_Sphere::Tool_Sphere()
	: Tool(),
	  m_center(0.0f), m_radius(5.0f)
{
}

void Tool_Sphere::onWheelScroll(int dl) {
	m_radius = std::max(m_radius + dl, 0);
}

void Tool_Sphere::onLeftClicDown(const Cursor& cursor) {
	History& history = Locate::history(HistoryType::Cubes);
	history.beginUndoGroup();
	generateSphere([](const glm::ivec3& pos) {Locate::cubesMap().addCube(pos); });
	history.endUndoGroup();
}

void Tool_Sphere::generateSphere(std::function<void(const glm::ivec3& pos)> addCube) {
	BoundingBox bbox(m_center, m_radius);
	for (const glm::ivec3& pos : bbox) {
		if( glm::length((const glm::vec3)(pos - m_center)) <= m_radius)
			addCube(pos);
	}
}

void Tool_Sphere::update(const Cursor& cursor) {
	m_center = cursor.getPosition();
	// preview
	m_previewGroup.removeAllCubes();
	generateSphere([this](const glm::ivec3& pos) {this->m_previewGroup.addCube_NoExistenceCheck(pos); });
}