#include "UniformConcrete.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

/*------------------------------------
------------------INT-----------------
--------------------------------------*/
template <>
void UniformConcrete<int>::sendTo(Shader& shader, const std::string& name) {
	shader.setUniform1i(name, value());
}
void UniformConcrete<int>::ImGui_Slider() {
	ImGui::PushID((int)&m_value);
	ImGui::SliderInt(getName().c_str(), &value(), m_minValue, m_maxValue);
	ImGui::PopID();
	pushChangeInHistory_IfNecessary();
}
void UniformConcrete<int>::ImGui_Drag(float speed) {
	ImGui::PushID((int)&m_value);
	ImGui::DragInt(getName().c_str(), &value(), speed);
	ImGui::PopID();
	pushChangeInHistory_IfNecessary();
}

/*------------------------------------
------------------FLOAT---------------
--------------------------------------*/
template <>
void UniformConcrete<float>::sendTo(Shader& shader, const std::string& name) {
	shader.setUniform1f(name, value());
}
void UniformConcrete<float>::ImGui_Slider() {
	ImGui::PushID((int)&m_value);
	ImGui::SliderFloat(getName().c_str(), &value(), m_minValue, m_maxValue);
	ImGui::PopID();
	pushChangeInHistory_IfNecessary();
}
void UniformConcrete<float>::ImGui_Drag(float speed) {
	ImGui::PushID((int)&m_value);
	ImGui::DragFloat(getName().c_str(), &value(), speed);
	ImGui::PopID();
	pushChangeInHistory_IfNecessary();
}

/*------------------------------------
------------------VEC2----------------
--------------------------------------*/
template <>
void UniformConcrete<glm::vec2>::sendTo(Shader& shader, const std::string& name) {
	shader.setUniform2f(name, value());
}
void UniformConcrete<glm::vec2>::ImGui_Slider() {
	ImGui::PushID((int)&m_value);
	ImGui::SliderFloat2(getName().c_str(), glm::value_ptr(value()), m_minValue.x, m_maxValue.x);
	ImGui::PopID();
	pushChangeInHistory_IfNecessary();
}
void UniformConcrete<glm::vec2>::ImGui_Drag(float speed) {
	ImGui::PushID((int)&m_value);
	ImGui::DragFloat2(getName().c_str(), glm::value_ptr(value()), speed);
	ImGui::PopID();
	pushChangeInHistory_IfNecessary();
}

/*------------------------------------
------------------VEC3----------------
--------------------------------------*/
template <>
void UniformConcrete<glm::vec3>::sendTo(Shader& shader, const std::string& name) {
	shader.setUniform3f(name, value());
}
void UniformConcrete<glm::vec3>::ImGui_Slider() {
	ImGui::PushID((int)&m_value);
	ImGui::ColorPicker3(getName().c_str(), glm::value_ptr(value()));
	ImGui::PopID();
	pushChangeInHistory_IfNecessary();
}
void UniformConcrete<glm::vec3>::ImGui_Drag(float speed) {
	ImGui::PushID((int)&m_value);
	ImGui::DragFloat3(getName().c_str(), glm::value_ptr(value()), speed);
	ImGui::PopID();
	pushChangeInHistory_IfNecessary();
}

/*------------------------------------
------------------VEC4----------------
--------------------------------------*/
template <>
void UniformConcrete<glm::vec4>::sendTo(Shader& shader, const std::string& name) {
	shader.setUniform4f(name, value());
}
void UniformConcrete<glm::vec4>::ImGui_Slider() {
	ImGui::PushID((int)&m_value);
	ImGui::ColorPicker4(getName().c_str(), glm::value_ptr(value()));
	ImGui::PopID();
	pushChangeInHistory_IfNecessary();
}
void UniformConcrete<glm::vec4>::ImGui_Drag(float speed) {
	ImGui::PushID((int)&m_value);
	ImGui::DragFloat4(getName().c_str(), glm::value_ptr(value()), speed);
	ImGui::PopID();
	pushChangeInHistory_IfNecessary();
}