#include "Tool_Shape_Radial.hpp"

#include "UI/Input.hpp"
#include <algorithm>

Tool_Shape_Radial::Tool_Shape_Radial()
	: m_radiuses(5)
{}

void Tool_Shape_Radial::onWheelScroll(int dl) {
	if (Input::KeyIsDown('x'))
		m_radiuses.x = std::max(m_radiuses.x + dl, 0);
	else if (Input::KeyIsDown('c'))
		m_radiuses.z = std::max(m_radiuses.z + dl, 0);
	else if (Input::KeyIsDown('v'))
		m_radiuses.y = std::max(m_radiuses.y + dl, 0);
	else {
		m_radiuses.x = std::max(m_radiuses.x + dl, 0);
		m_radiuses.y = std::max(m_radiuses.y + dl, 0);
		m_radiuses.z = std::max(m_radiuses.z + dl, 0);
	}
}

void Tool_Shape_Radial::update(const Cursor& cursor) {
	m_center = cursor.getCubeJustBeforePosition();
	computePreview();
	if (Input::KeyIsDown(SPACE))
		replaceMaterials();
}