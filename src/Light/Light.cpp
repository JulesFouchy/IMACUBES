#include "Light.hpp"
#include <imgui/imgui.h>
#include "Debugging/Log.hpp"

Light::Light(const std::string& name, const glm::vec3& color, float intensity, float intensityDragSpeed)
    : m_name(name), m_color("Color", HistoryType::Lights, color), m_intensity("Intensity", HistoryType::Lights, intensity), m_intensityDragSpeed(intensityDragSpeed)
{}

void Light::setUniforms(const std::string& uniformName, UniformUpdateList& uniformsList)
{
    uniformsList.setUniform(uniformName + ".color", m_color.getValue());
    uniformsList.setUniform(uniformName + ".intensity", m_intensity.getValue());
}

void Light::ImGui_Sliders()
{
    m_color.ImGui_Slider();
    m_intensity.ImGui_Drag(m_intensityDragSpeed);
    bool bPushChangeInHistory = ImGui::IsItemDeactivatedAfterEdit();
    if (m_intensity.getValue() < -0.0001f)
        m_intensity.setValue(0.0f, bPushChangeInHistory);
}