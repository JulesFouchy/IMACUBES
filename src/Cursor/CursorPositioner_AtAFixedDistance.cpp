#include "CursorPositioner_AtAFixedDistance.hpp"
#include <algorithm>
#include "Camera/Camera.hpp"
#include "CubeMaths/CubeMaths.hpp"
#include "CubesMap/CubesMap.hpp"
#include "Cursor.hpp"
#include "Debugging/Log.hpp"
#include "Locator/Locate.hpp"
#include "UI/Settings.hpp"

CursorPositioner_AtAFixedDistance::CursorPositioner_AtAFixedDistance(Cursor* cursor)
    : CursorPositioner(cursor), m_distance(29.0f)
{}

void CursorPositioner_AtAFixedDistance::computePosition()
{
    Camera&   camera   = Locate::camera();
    CubesMap& cubesMap = Locate::cubesMap();
    Ray       ray      = camera.getRayGoingThroughMousePos();

    glm::ivec3 pos = CubeMaths::CubeContaining(ray.origin + m_distance * ray.direction);
    if (!cubesMap.isID3Dvalid(pos))
    {
        float offset = cubesMap.isPositionInsideWorld(camera.getPosition()) ? -2.0f : 1.0f;
        pos          = CubeMaths::CubeContaining(ray.origin + (CubeMaths::IntersectionRayWorldborder(ray) + offset) * ray.direction);
    }

    m_cursor->setCubeJustBeforePosition(pos);
    m_cursor->setPosition(pos);
    m_cursor->m_normalOfHoveredFace = glm::ivec3(0);
}

void CursorPositioner_AtAFixedDistance::onWheelScroll(float dl)
{
    m_distance = std::max(m_distance + dl * Settings::CAMERA_SCALE_RADIUS_PER_SCROLL, 0.0f);
    computePosition();
}