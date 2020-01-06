#include "Tool_Cube.hpp"

#include "CubesMap/BoundingBox.hpp"

void Tool_Cube::applyOnShape(std::function<void(const glm::ivec3 & pos)> whatToDoWithPos) {
	BoundingBox bbox(m_center, m_radiuses, CENTER);
	for (const glm::ivec3& pos : bbox) {
		whatToDoWithPos(pos);
	}
}