#include "Tool_BoxTwoCorners.hpp"
#include "CubesMap/BoundingBox.hpp"

void Tool_BoxTwoCorners::applyOnShape(std::function<void(const glm::ivec3& pos)> whatToDoWithPos)
{
    computeBoundingBox();
    for (const glm::ivec3& pos : m_bbox)
        whatToDoWithPos(pos);
}