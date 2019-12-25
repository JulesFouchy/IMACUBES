#include "PointLight.hpp"

#include <imgui/imgui.h>

PointLight::PointLight(const glm::vec3& position, const std::string& name, const glm::vec3& color, float intensity)
	: Light(name, color, intensity), m_position(position)
{}

void PointLight::setUniforms(const std::string & uniformName, UniformUpdateList & uniformsList) {
	Light::setUniforms(uniformName, uniformsList);
	uniformsList.setUniform(uniformName + ".position", m_position);
}

void PointLight::ImGui_Sliders() {
	Light::ImGui_Sliders();
	ImGui::Separator();
	ImGui::DragFloat3("Position", (float*)&m_position);
}