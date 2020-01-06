#include "Tool_OvoidTwoCorners.hpp"

#include "Helper/Maths.hpp"

void Tool_OvoidTwoCorners::applyOnShape(std::function<void(const glm::ivec3 & pos)> whatToDoWithPos) {
	computeBoundingBox();
	int nbDimensions = (m_bbox.size().x != 0 ? 1 : 0)
					 + (m_bbox.size().y != 0 ? 1 : 0)
					 + (m_bbox.size().z != 0 ? 1 : 0);
	if (nbDimensions == 3) {
		for (const glm::ivec3& pos : m_bbox) {
			if (glm::length((glm::vec3)(pos - m_bbox.center()) / (glm::vec3)m_bbox.size()) <= 0.5f)
				whatToDoWithPos(pos);
		}
	}
	else if (nbDimensions == 2) { // to prevent divisions by 0 when dividing by bbox.size()
		int c0, c1;
		if      (m_bbox.size().x == 0) { c0 = 1; c1 = 2; }
		else if (m_bbox.size().y == 0) { c0 = 0; c1 = 2; }
		else                           { c0 = 0; c1 = 1; }
		for (const glm::ivec3& pos : m_bbox) {
			if (MyMaths::NormalizedDistance2D(pos, m_bbox.center(), m_bbox.size(), c0, c1) <= 0.5f)
				whatToDoWithPos(pos);
		}
	}
	else {
		for (const glm::ivec3& pos : m_bbox)
			whatToDoWithPos(pos);
	}
}