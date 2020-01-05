#include "CursorPositioner_OnHoveredCube.hpp"

#include "Cursor.hpp"

#include "CubeMaths/CubeMaths.hpp"

#include "Locator/Locate.hpp"
#include "Camera/Camera.hpp"
#include "CubesMap/CubesMap.hpp"

CursorPositioner_OnHoveredCube::CursorPositioner_OnHoveredCube(Cursor* cursor)
	: CursorPositioner(cursor)
{}

void CursorPositioner_OnHoveredCube::computePosition() {
	Camera& camera = Locate::camera();
	CubesMap& cubesMap = Locate::cubesMap();
	Ray ray = camera.getRayGoingThroughMousePos();
	if (!cubesMap.isPositionInsideWorld(ray.origin)) {
		float t = CubeMaths::IntersectionRayWorldborder(ray);
		if (t < std::numeric_limits<float>::infinity())
			ray.origin += (t + 0.01f) * ray.direction;
		else
			return;
	}
	glm::ivec3 iPos = CubeMaths::CubeContaining(ray.origin);
	glm::ivec3 prevIpos = iPos;
	while (cubesMap.isID3Dvalid(iPos) && !cubesMap.cubeExists(iPos)) {
		float t = CubeMaths::IntersectionRayCube_WROIC(ray, iPos);
		ray.origin += (t + 0.01f) * ray.direction;
		iPos = CubeMaths::CubeContaining(ray.origin);
		if (cubesMap.isID3Dvalid(iPos) && !cubesMap.cubeExists(iPos))
			prevIpos = iPos;
	}
	if (cubesMap.isID3Dvalid(prevIpos)) {
		m_cursor->setCubeJustBeforePosition(prevIpos);
	}
	if (cubesMap.isID3Dvalid(iPos)) {
		m_cursor->setPosition(iPos);
	}
	else {
		if (cubesMap.isID3Dvalid(prevIpos)) {
			m_cursor->setPosition(prevIpos);
		}
	}
}