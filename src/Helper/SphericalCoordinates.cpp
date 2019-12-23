#include "SphericalCoordinates.hpp"

#include "Maths.hpp"

#include "Debugging/Log.hpp"

#include <imgui/imgui.h>

void SphericalCoordinates::computeXYZ() {
	using namespace MyMaths;
	m_x = getRadius() * Cos(getAngleUp()) * Cos(getAngleGround());
	m_y = getRadius() * Sin(getAngleUp());
	m_z = getRadius() * Cos(getAngleUp()) * Sin(getAngleGround());
	m_bMustRecomputeXYZ = false;
}

bool SphericalCoordinates::_ImGui_CoordinatesSliders() {
	bool modifs = ImGui::SliderAngle("Angle Ground", &m_angleGround);
	modifs |=     ImGui::SliderAngle("Angle Up", &m_angleUp);
	modifs |=     ImGui::DragFloat("Distance", &m_radius, 1.0f);
	if (m_radius < 0.5f) 
		m_radius = 0.5f;
	if (modifs)
		m_bMustRecomputeXYZ = true;
	return modifs;
}