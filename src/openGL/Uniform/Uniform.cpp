#include "Uniform.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Helper/SphericalCoordinates_AngularPart.hpp"

/*------------------------------------
------------------INT-----------------
--------------------------------------*/
template<>
void Uniform<int>::sendTo(Shader& shader, const std::string& name)
{
    shader.setUniform1i(name, value());
}
bool Uniform<int>::ImGui_Slider()
{
    ImGui::PushID((int)&m_value);
    bool b = ImGui::SliderInt(getName().c_str(), &value(), m_minValue, m_maxValue);
    ImGui::PopID();
    pushChangeInHistory_IfNecessary();
    return b;
}
bool Uniform<int>::ImGui_Drag(float speed)
{
    ImGui::PushID((int)&m_value);
    bool b = ImGui::DragInt(getName().c_str(), &value(), speed);
    ImGui::PopID();
    pushChangeInHistory_IfNecessary();
    return b;
}

/*------------------------------------
------------------FLOAT---------------
--------------------------------------*/
template<>
void Uniform<float>::sendTo(Shader& shader, const std::string& name)
{
    shader.setUniform1f(name, value());
}
bool Uniform<float>::ImGui_Slider()
{
    ImGui::PushID((int)&m_value);
    bool b = ImGui::SliderFloat(getName().c_str(), &value(), m_minValue, m_maxValue);
    ImGui::PopID();
    pushChangeInHistory_IfNecessary();
    return b;
}
bool Uniform<float>::ImGui_Drag(float speed)
{
    ImGui::PushID((int)&m_value);
    bool b = ImGui::DragFloat(getName().c_str(), &value(), speed);
    ImGui::PopID();
    pushChangeInHistory_IfNecessary();
    return b;
}

/*------------------------------------
------------------VEC2----------------
--------------------------------------*/
template<>
void Uniform<glm::vec2>::sendTo(Shader& shader, const std::string& name)
{
    shader.setUniform2f(name, value());
}
bool Uniform<glm::vec2>::ImGui_Slider()
{
    ImGui::PushID((int)&m_value);
    bool b = ImGui::SliderFloat2(getName().c_str(), glm::value_ptr(value()), m_minValue.x, m_maxValue.x);
    ImGui::PopID();
    pushChangeInHistory_IfNecessary();
    return b;
}
bool Uniform<glm::vec2>::ImGui_Drag(float speed)
{
    ImGui::PushID((int)&m_value);
    bool b = ImGui::DragFloat2(getName().c_str(), glm::value_ptr(value()), speed);
    ImGui::PopID();
    pushChangeInHistory_IfNecessary();
    return b;
}

/*------------------------------------
------------------VEC3----------------
--------------------------------------*/
template<>
void Uniform<glm::vec3>::sendTo(Shader& shader, const std::string& name)
{
    shader.setUniform3f(name, value());
}
bool Uniform<glm::vec3>::ImGui_Slider()
{
    ImGui::PushID((int)&m_value);
    bool b = ImGui::ColorPicker3(getName().c_str(), glm::value_ptr(value()));
    ImGui::PopID();
    pushChangeInHistory_IfNecessary();
    return b;
}
bool Uniform<glm::vec3>::ImGui_Drag(float speed)
{
    ImGui::PushID((int)&m_value);
    bool b = ImGui::DragFloat3(getName().c_str(), glm::value_ptr(value()), speed);
    ImGui::PopID();
    pushChangeInHistory_IfNecessary();
    return b;
}

/*------------------------------------
------------------VEC4----------------
--------------------------------------*/
template<>
void Uniform<glm::vec4>::sendTo(Shader& shader, const std::string& name)
{
    shader.setUniform4f(name, value());
}
bool Uniform<glm::vec4>::ImGui_Slider()
{
    ImGui::PushID((int)&m_value);
    bool b = ImGui::ColorPicker4(getName().c_str(), glm::value_ptr(value()));
    ImGui::PopID();
    pushChangeInHistory_IfNecessary();
    return b;
}
bool Uniform<glm::vec4>::ImGui_Drag(float speed)
{
    ImGui::PushID((int)&m_value);
    bool b = ImGui::DragFloat4(getName().c_str(), glm::value_ptr(value()), speed);
    ImGui::PopID();
    pushChangeInHistory_IfNecessary();
    return b;
}

/*------------------------------------
---SphericalCoordinates_AngularPart---
--------------------------------------*/
template<>
void Uniform<SphericalCoordinates_AngularPart>::sendTo(Shader& shader, const std::string& name)
{
    shader.setUniform2f(name, glm::vec2(value().angleUp(), value().angleGround()));
}
bool Uniform<SphericalCoordinates_AngularPart>::ImGui_Slider()
{
    ImGui::PushID((int)&m_value);
    bool b = value()._ImGui_AngleUpSlider();
    pushChangeInHistory_IfNecessary();
    b |= value()._ImGui_AngleGroundSlider();
    pushChangeInHistory_IfNecessary();
    ImGui::PopID();
    return b;
}
bool Uniform<SphericalCoordinates_AngularPart>::ImGui_Drag(float speed)
{
    return ImGui_Slider();
}