#include "Tool_Sphere.hpp"

#include "Helper/Maths.hpp"

#include "CubesMap/BoundingBox.hpp"

void Tool_Sphere::applyOnShape(std::function<void(const glm::ivec3 & pos)> whatToDoWithPos) {
	BoundingBox bbox(m_center, m_radiuses, CENTER);
	int nbDimensions = (bbox.size().x != 0 ? 1 : 0)
		+ (bbox.size().y != 0 ? 1 : 0)
		+ (bbox.size().z != 0 ? 1 : 0);
	if (nbDimensions == 3) {
		for (const glm::ivec3& pos : bbox) {
			if (glm::length((glm::vec3)(pos - bbox.center()) / (glm::vec3)bbox.size()) <= 0.5f)
				whatToDoWithPos(pos);
		}
	}
	else if (nbDimensions == 2) { // to prevent divisions by 0
		int c0, c1;
		if (bbox.size().x == 0) { c0 = 1; c1 = 2; }
		else if (bbox.size().y == 0) { c0 = 0; c1 = 2; }
		else { c0 = 0; c1 = 1; }
		for (const glm::ivec3& pos : bbox) {
			if (MyMaths::NormalizedDistance2D(pos, bbox.center(), bbox.size(), c0, c1) <= 0.5f)
				whatToDoWithPos(pos);
		}
	}
	else {
		for (const glm::ivec3& pos : bbox)
			whatToDoWithPos(pos);
	}
}