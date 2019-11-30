#include "UniformConcrete.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

/*------------------------------------
------------------INT-----------------
--------------------------------------*/
template <>
void UniformConcrete<int>::set(int structIndex) {
	m_shader->setUniform1i(getNameFull(structIndex), m_value);
}
std::tuple<bool, bool, bool> UniformConcrete<int>::ImGui_Slider() {
	ImGui::PushID((int)&m_value);
	bool wasJusModified = ImGui::SliderInt(getNameInsideStruct().c_str(), &m_value, m_minValue, m_maxValue);
	ImGui::PopID();
	return std::make_tuple(wasJusModified, ImGui::IsItemActivated(), ImGui::IsItemDeactivatedAfterEdit());
}

/*------------------------------------
------------------FLOAT---------------
--------------------------------------*/
template <>
void UniformConcrete<float>::set(int structIndex) {
	m_shader->setUniform1f(getNameFull(structIndex), m_value);
}
std::tuple<bool, bool, bool> UniformConcrete<float>::ImGui_Slider() {
	ImGui::PushID((int)&m_value);
	bool wasJusModified = ImGui::SliderFloat(getNameInsideStruct().c_str(), &m_value, m_minValue, m_maxValue);
	ImGui::PopID();
	return std::make_tuple(wasJusModified, ImGui::IsItemActivated(), ImGui::IsItemDeactivatedAfterEdit());
}

/*------------------------------------
------------------VEC2----------------
--------------------------------------*/
template <>
void UniformConcrete<glm::vec2>::set(int structIndex) {
	m_shader->setUniform2f(getNameFull(structIndex), m_value);
}
std::tuple<bool, bool, bool> UniformConcrete<glm::vec2>::ImGui_Slider() {
	ImGui::PushID((int)&m_value);
	bool wasJusModified = ImGui::SliderFloat2(getNameInsideStruct().c_str(), glm::value_ptr(m_value), m_minValue.x, m_maxValue.x);
	ImGui::PopID();
	return std::make_tuple(wasJusModified, ImGui::IsItemActivated(), ImGui::IsItemDeactivatedAfterEdit());
}

/*------------------------------------
------------------VEC3----------------
--------------------------------------*/
template <>
void UniformConcrete<glm::vec3>::set(int structIndex) {
	m_shader->setUniform3f(getNameFull(structIndex), m_value);
}
std::tuple<bool, bool, bool> UniformConcrete<glm::vec3>::ImGui_Slider() {
	ImGui::PushID((int)&m_value);
	bool wasJusModified = ImGui::ColorPicker3(getNameInsideStruct().c_str(), glm::value_ptr(m_value));
	ImGui::PopID();
	return std::make_tuple(wasJusModified, ImGui::IsItemActivated(), ImGui::IsItemDeactivatedAfterEdit());
}

/*------------------------------------
------------------VEC4----------------
--------------------------------------*/
template <>
void UniformConcrete<glm::vec4>::set(int structIndex) {
	m_shader->setUniform4f(getNameFull(structIndex), m_value);
}
std::tuple<bool, bool, bool> UniformConcrete<glm::vec4>::ImGui_Slider() {
	ImGui::PushID((int)&m_value);
	bool wasJusModified = ImGui::ColorPicker4(getNameInsideStruct().c_str(), glm::value_ptr(m_value));
	ImGui::PopID();
	return std::make_tuple(wasJusModified, ImGui::IsItemActivated(), ImGui::IsItemDeactivatedAfterEdit());
}