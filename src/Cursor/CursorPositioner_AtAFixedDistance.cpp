#include "CursorPositioner_AtAFixedDistance.hpp"

#include "Cursor.hpp"

#include "CubeMaths/CubeMaths.hpp"

#include "Locator/Locate.hpp"
#include "CubesMap/CubesMap.hpp"
#include "Camera/Camera.hpp"

#include "Debugging/Log.hpp"

#include "UI/Settings.hpp"

#include <algorithm>

CursorPositioner_AtAFixedDistance::CursorPositioner_AtAFixedDistance(Cursor* cursor)
	: CursorPositioner(cursor), m_distance(10.0f)
{}

void CursorPositioner_AtAFixedDistance::computePosition() {
	Camera& camera = Locate::camera();
	CubesMap& cubesMap = Locate::cubesMap();
	Ray ray = camera.getRayGoingThroughMousePos();

	glm::ivec3 pos = CubeMaths::CubeContaining(ray.origin + m_distance * ray.direction);
	if (!cubesMap.isID3Dvalid(pos)){
		float offset = cubesMap.isPositionInsideWorld(camera.getPosition()) ? -2.0f : 1.0f;
		pos = CubeMaths::CubeContaining(ray.origin + (CubeMaths::IntersectionRayWorldborder(ray)+offset) * ray.direction);
	}

	m_cursor->setCubeJustBeforePosition(pos);
	m_cursor->setPosition(pos);
}

void CursorPositioner_AtAFixedDistance::onWheelScroll(float dl) {
	m_distance = std::max(m_distance + dl * Settings::CAMERA_SCALE_RADIUS_PER_SCROLL, 0.0f);
	computePosition();
}