#include "Helper/SphericalCoordinates_AngularPart.hpp"

#include "Maths.hpp"

#include <imgui/imgui.h>

void SphericalCoordinates_AngularPart::computeXYZ() {
	using namespace MyMaths;
	m_xyz.x = Cos(getAngleUp()) * Cos(getAngleGround());
	m_xyz.y = Sin(getAngleUp());
	m_xyz.z = Cos(getAngleUp()) * Sin(getAngleGround());
	m_bMustRecomputeXYZ = false;
}

bool SphericalCoordinates_AngularPart::_ImGui_CoordinatesSliders() {
	bool modifs = ImGui::SliderAngle("Angle Up", &angleUp(), -180, 0);
	modifs |=     ImGui::SliderAngle("Angle Ground", &angleGround());
	if (modifs)
		m_bMustRecomputeXYZ = true;
	return modifs;
}