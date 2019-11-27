#include "UniformConcrete.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

template <>
void UniformConcrete<int>::set() {
	glUniform1i(getLocation(), m_value);
}
std::tuple<bool, bool, bool> UniformConcrete<int>::ImGui_Slider() {
	ImGui::PushID((int)&m_value);
	bool wasJusModified = ImGui::SliderInt(getName().c_str(), &m_value, m_minValue, m_maxValue);
	ImGui::PopID();
	return std::make_tuple(wasJusModified, ImGui::IsItemActivated(), ImGui::IsItemDeactivatedAfterEdit());
}

template <>
void UniformConcrete<float>::set() {
	glUniform1f(getLocation(), m_value);
}
std::tuple<bool, bool, bool> UniformConcrete<float>::ImGui_Slider() {
	ImGui::PushID((int)&m_value);
	bool wasJusModified = ImGui::SliderFloat(getName().c_str(), &m_value, m_minValue, m_maxValue);
	ImGui::PopID();
	return std::make_tuple(wasJusModified, ImGui::IsItemActivated(), ImGui::IsItemDeactivatedAfterEdit());
}

template <>
void UniformConcrete<glm::vec2>::set() {
	glUniform2f(getLocation(), m_value.x, m_value.y);
}
std::tuple<bool, bool, bool> UniformConcrete<glm::vec2>::ImGui_Slider() {
	ImGui::PushID((int)&m_value);
	bool wasJusModified = ImGui::SliderFloat2(getName().c_str(), glm::value_ptr(m_value), m_minValue.x, m_maxValue.x);
	ImGui::PopID();
	return std::make_tuple(wasJusModified, ImGui::IsItemActivated(), ImGui::IsItemDeactivatedAfterEdit());
}

template <>
void UniformConcrete<glm::vec3>::set() {
	glUniform3f(getLocation(), m_value.x, m_value.y, m_value.z);
}
std::tuple<bool, bool, bool> UniformConcrete<glm::vec3>::ImGui_Slider() {
	ImGui::PushID((int)&m_value);
	bool wasJusModified = ImGui::SliderFloat3(getName().c_str(), glm::value_ptr(m_value), m_minValue.x, m_maxValue.x);
	ImGui::PopID();
	return std::make_tuple(wasJusModified, ImGui::IsItemActivated(), ImGui::IsItemDeactivatedAfterEdit());
}

template <>
void UniformConcrete<glm::vec4>::set() {
	glUniform4f(getLocation(), m_value.x, m_value.y, m_value.z, m_value.w);
}
std::tuple<bool, bool, bool> UniformConcrete<glm::vec4>::ImGui_Slider() {
	ImGui::PushID((int)&m_value);
	bool wasJusModified = ImGui::SliderFloat4(getName().c_str(), glm::value_ptr(m_value), m_minValue.x, m_maxValue.x);
	ImGui::PopID();
	return std::make_tuple(wasJusModified, ImGui::IsItemActivated(), ImGui::IsItemDeactivatedAfterEdit());
}