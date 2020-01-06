#include "PointLight.hpp"

#include <imgui/imgui.h>

PointLight::PointLight(const glm::vec3& position, const glm::vec3& color, float intensity, const std::string& name)
	: Light(name, color, intensity, 10.0f), m_position("Position", HistoryType::Lights, position)
{}

void PointLight::setUniforms(const std::string & uniformName, UniformUpdateList & uniformsList) {
	Light::setUniforms(uniformName, uniformsList);
	uniformsList.setUniform(uniformName + ".position", m_position.getValue());
}

void PointLight::ImGui_Sliders() {
	Light::ImGui_Sliders();
	ImGui::Separator();
	m_position.ImGui_Drag(0.2f);
}