#include "DirectionalLight.hpp"

#include <imgui/imgui.h>

DirectionalLight::DirectionalLight(float angleUp, float angleGround, const glm::vec3& color, float intensity, const std::string& name)
	: Light(name, color, intensity), m_direction("", HistoryType::Lights, SphericalCoordinates_AngularPart(angleUp, angleGround))
{}

void DirectionalLight::setUniforms(const std::string& uniformName, UniformUpdateList& uniformsList) {
	Light::setUniforms(uniformName, uniformsList);
	glm::vec3 dirNormalized = m_direction.value().getXYZ() / glm::length(m_direction.value().getXYZ());
	uniformsList.setUniform(uniformName + ".direction", dirNormalized);
}

void DirectionalLight::ImGui_Sliders() {
	Light::ImGui_Sliders();
	ImGui::Separator();
	m_direction.ImGui_Slider();
}