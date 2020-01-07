#include "Tool_Shape_Radial.hpp"

#include "UI/Input.hpp"
#include <algorithm>

#include <imgui/imgui.h>

#include <limits>

#include "Debugging/Log.hpp"

int Tool_Shape_Radial::m_bCenterOnHoveredCube = 1;

Tool_Shape_Radial::Tool_Shape_Radial()
	: m_sizes(11)
{}

void Tool_Shape_Radial::onWheelScroll(int dl) {
	if (Input::KeyIsDown('x'))
		m_sizes.x = std::max(m_sizes.x + dl, 1);
	else if (Input::KeyIsDown('c'))
		m_sizes.z = std::max(m_sizes.z + dl, 1);
	else if (Input::KeyIsDown('v'))
		m_sizes.y = std::max(m_sizes.y + dl, 1);
	else {
		m_sizes.x = std::max(m_sizes.x + dl, 1);
		m_sizes.y = std::max(m_sizes.y + dl, 1);
		m_sizes.z = std::max(m_sizes.z + dl, 1);
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
	m_bbox = BoundingBox(m_center + m_direction * m_sizes/2, m_sizes, CENTER_SIZE);
}

void Tool_Shape_Radial::ImGui_Menu() {
	Tool_Shape::ImGui_Menu();
	ImGui::PushID((int)this);
	ImGui::Combo("", &m_bCenterOnHoveredCube, " Kiss hovered cube\0 Center on hovered cube\0\0");
	ImGui::PopID();
	ImGui::DragInt3("Sizes", &m_sizes.x, 1.0f, 1, std::numeric_limits<int>::max()/2);
}