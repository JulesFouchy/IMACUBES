#include "Tool_Cube.hpp"

void Tool_Cube::applyOnShape(std::function<void(const glm::ivec3& pos)> whatToDoWithPos)
{
    computeBoundingBox();
    for (const glm::ivec3& pos : m_bbox)
    {
        whatToDoWithPos(pos);
    }
}