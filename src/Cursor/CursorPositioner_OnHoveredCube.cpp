#include "CursorPositioner_OnHoveredCube.hpp"
#include "Camera/Camera.hpp"
#include "CubeMaths/CubeMaths.hpp"
#include "CubesMap/CubesMap.hpp"
#include "Cursor.hpp"
#include "Locator/Locate.hpp"

CursorPositioner_OnHoveredCube::CursorPositioner_OnHoveredCube(Cursor* cursor)
    : CursorPositioner(cursor)
{}

void CursorPositioner_OnHoveredCube::computePosition()
{
    Camera&   camera   = Locate::camera();
    CubesMap& cubesMap = Locate::cubesMap();
    Ray       ray      = camera.getRayGoingThroughMousePos();
    if (!cubesMap.isPositionInsideWorld(ray.origin))
    {
        float t = CubeMaths::IntersectionRayWorldborder(ray);
        if (t < std::numeric_limits<float>::infinity())
            ray.origin += (t + 0.01f) * ray.direction;
        else
            return;
    }
    glm::ivec3 iPos     = CubeMaths::CubeContaining(ray.origin);
    glm::ivec3 prevIpos = iPos;
    while (cubesMap.isID3Dvalid(iPos) && !cubesMap.cubeExists(iPos))
    {
        float t = CubeMaths::IntersectionRayCube_WROIC(ray, iPos);
        ray.origin += (t + 0.01f) * ray.direction;
        prevIpos = iPos;
        iPos     = CubeMaths::CubeContaining(ray.origin);
    }
    m_cursor->setCubeJustBeforePosition(prevIpos);
    if (cubesMap.isID3Dvalid(iPos))
    {
        m_cursor->setPosition(iPos);
        m_cursor->m_normalOfHoveredFace = prevIpos - iPos;
    }
    else
    {
        m_cursor->setPosition(prevIpos);
        if (iPos.x < cubesMap.minValidX())
            m_cursor->m_normalOfHoveredFace = glm::ivec3(1, 0, 0);
        else if (iPos.x > cubesMap.maxValidX())
            m_cursor->m_normalOfHoveredFace = glm::ivec3(-1, 0, 0);
        else if (iPos.y < cubesMap.minValidY())
            m_cursor->m_normalOfHoveredFace = glm::ivec3(0, 1, 0);
        else if (iPos.y > cubesMap.maxValidY())
            m_cursor->m_normalOfHoveredFace = glm::ivec3(0, -1, 0);
        else if (iPos.z < cubesMap.minValidZ())
            m_cursor->m_normalOfHoveredFace = glm::ivec3(0, 0, 1);
        else if (iPos.z > cubesMap.maxValidZ())
            m_cursor->m_normalOfHoveredFace = glm::ivec3(0, 0, -1);
    }
}