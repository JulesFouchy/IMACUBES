#include "DirectionalLight.hpp"

#include <imgui/imgui.h>

DirectionalLight::DirectionalLight(const glm::vec3& direction, const glm::vec3& color, float intensity, const std::string& name)
	: Light(name, color, intensity), m_direction(direction)
{}

void DirectionalLight::setUniforms(const std::string& uniformName, UniformUpdateList& uniformsList) {
	Light::setUniforms(uniformName, uniformsList);
	glm::vec3 dirNormalized = m_direction / glm::length(m_direction);
	uniformsList.setUniform(uniformName + ".direction", dirNormalized);
}

void DirectionalLight::ImGui_Sliders() {
	Light::ImGui_Sliders();
	ImGui::Separator();
	ImGui::DragFloat3("Direction", (float*)&m_direction);
}