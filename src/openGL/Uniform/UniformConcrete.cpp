#include "UniformConcrete.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Locator/HistoryLocator.hpp"

/*------------------------------------
------------------INT-----------------
--------------------------------------*/
template <>
void UniformConcrete<int>::set(int structIndex) {
	getShader().setUniform1i(getNameFull(structIndex), m_value);
}
void UniformConcrete<int>::ImGui_Slider() {
	ImGui::PushID((int)&m_value);
	ImGui::SliderInt(getNameInsideStruct().c_str(), &m_value, m_minValue, m_maxValue);
	ImGui::PopID();
	pushChangeInHistory_IfNecessary();
}

/*------------------------------------
------------------FLOAT---------------
--------------------------------------*/
template <>
void UniformConcrete<float>::set(int structIndex) {
	getShader().setUniform1f(getNameFull(structIndex), m_value);
}
void UniformConcrete<float>::ImGui_Slider() {
	ImGui::PushID((int)&m_value);
	ImGui::SliderFloat(getNameInsideStruct().c_str(), &m_value, m_minValue, m_maxValue);
	ImGui::PopID();
	pushChangeInHistory_IfNecessary();
}

/*------------------------------------
------------------VEC2----------------
--------------------------------------*/
template <>
void UniformConcrete<glm::vec2>::set(int structIndex) {
	getShader().setUniform2f(getNameFull(structIndex), m_value);
}
void UniformConcrete<glm::vec2>::ImGui_Slider() {
	ImGui::PushID((int)&m_value);
	ImGui::SliderFloat2(getNameInsideStruct().c_str(), glm::value_ptr(m_value), m_minValue.x, m_maxValue.x);
	ImGui::PopID();
	pushChangeInHistory_IfNecessary();
}

/*------------------------------------
------------------VEC3----------------
--------------------------------------*/
template <>
void UniformConcrete<glm::vec3>::set(int structIndex) {
	getShader().setUniform3f(getNameFull(structIndex), m_value);
}
void UniformConcrete<glm::vec3>::ImGui_Slider() {
	ImGui::PushID((int)&m_value);
	ImGui::ColorPicker3(getNameInsideStruct().c_str(), glm::value_ptr(m_value));
	ImGui::PopID();
	pushChangeInHistory_IfNecessary();
}

/*------------------------------------
------------------VEC4----------------
--------------------------------------*/
template <>
void UniformConcrete<glm::vec4>::set(int structIndex) {
	getShader().setUniform4f(getNameFull(structIndex), m_value);
}
void UniformConcrete<glm::vec4>::ImGui_Slider() {
	ImGui::PushID((int)&m_value);
	ImGui::ColorPicker4(getNameInsideStruct().c_str(), glm::value_ptr(m_value));
	ImGui::PopID();
	pushChangeInHistory_IfNecessary();
}