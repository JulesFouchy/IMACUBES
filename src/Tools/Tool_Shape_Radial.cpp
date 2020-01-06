#include "Tool_Shape_Radial.hpp"

#include "UI/Input.hpp"
#include <algorithm>

#include <imgui/imgui.h>

#include "Debugging/Log.hpp"

Tool_Shape_Radial::Tool_Shape_Radial()
	: m_radiuses(5), m_bCenterOnHoveredCube(0)
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
	m_direction = m_bCenterOnHoveredCube ? glm::ivec3(0) : cursor.getCubeJustBeforePosition() - cursor.getPosition();
	computePreview();
	if (Input::KeyIsDown(SPACE))
		replaceMaterials();
}

void Tool_Shape_Radial::computeBoundingBox() {
	m_bbox = BoundingBox(m_center + m_direction * m_radiuses, m_radiuses, CENTER);
}

void Tool_Shape_Radial::ImGui_Menu() {
	Tool_Shape::ImGui_Menu();
	ImGui::PushID((int)this);
	ImGui::Combo("", &m_bCenterOnHoveredCube, " Kiss hovered cube\0 Center on hovered cube\0\0");
	ImGui::PopID();
}