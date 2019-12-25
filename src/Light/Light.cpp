#include "Light.hpp"

#include <imgui/imgui.h>

Light::Light(const std::string& name, const glm::vec3& color, float intensity)
	: m_name(name), m_color(color), m_intensity(intensity)
{}

void Light::setUniforms(const std::string & uniformName, UniformUpdateList & uniformsList) {
	uniformsList.setUniform(uniformName + ".color", m_color);
	uniformsList.setUniform(uniformName + ".intensity", m_intensity);
}

void Light::ImGui_Sliders() {
	ImGui::ColorPicker3("Color", (float*)&m_color);
	ImGui::DragFloat("Intensity", &m_intensity, 0.01f);
	if (m_intensity < 0.0f)
		m_intensity = 0.0f;
}