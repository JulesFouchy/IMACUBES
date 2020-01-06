#include "Tool_BoxTwoCorners.hpp"

#include "CubesMap/BoundingBox.hpp"

void Tool_BoxTwoCorners::applyOnShape(std::function<void(const glm::ivec3 & pos)> whatToDoWithPos) {
	BoundingBox bbox(m_corner1, m_corner2, CORNERS);
	for (const glm::ivec3& pos : bbox)
		whatToDoWithPos(pos);
}