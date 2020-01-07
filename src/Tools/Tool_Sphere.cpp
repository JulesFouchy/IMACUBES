#include "Tool_Sphere.hpp"

void Tool_Sphere::applyOnShape(std::function<void(const glm::ivec3 & pos)> whatToDoWithPos) {
	computeBoundingBox();
	glm::vec3 center = (glm::vec3)(m_center + m_direction * m_sizes / 2) - 0.5f * (glm::vec3)(1 - m_sizes % 2);
	for (const glm::ivec3& pos : m_bbox) {
		if (glm::length(((glm::vec3)(pos) - center) / (glm::vec3)(m_sizes)) <= 0.5f)
			whatToDoWithPos(pos);
	}
}