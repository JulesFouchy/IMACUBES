#include "Light.hpp"

#include <imgui/imgui.h>

Light::Light(const std::string& name, const glm::vec3& color, float intensity)
	: m_name(name), m_color("Color", HistoryType::Lights, color), m_intensity("Intensity", HistoryType::Lights, intensity)
{}

void Light::setUniforms(const std::string & uniformName, UniformUpdateList & uniformsList) {
	uniformsList.setUniform(uniformName + ".color", m_color.getValue());
	uniformsList.setUniform(uniformName + ".intensity", m_intensity.getValue());
}

void Light::ImGui_Sliders() {
	m_color.ImGui_Slider();
	m_intensity.ImGui_Drag(0.01f);
	if (m_intensity.getValue() < 0.0f)
		m_intensity.setValue(0.0f);
}