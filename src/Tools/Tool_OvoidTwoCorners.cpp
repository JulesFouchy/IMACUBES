#include "Tool_OvoidTwoCorners.hpp"

void Tool_OvoidTwoCorners::applyOnShape(std::function<void(const glm::ivec3 & pos)> whatToDoWithPos) {
	computeBoundingBox();
	for (const glm::ivec3& pos : m_bbox) {
		if (glm::length( ((glm::vec3)pos - m_bbox.centerFloat()) / (glm::vec3)m_bbox.size() ) <= 0.5f)
			whatToDoWithPos(pos);
	}
}