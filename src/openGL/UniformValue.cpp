#include "UniformValue.hpp"

template <>
void UniformValueConcrete<int>::set(const std::string& uniforName, Shader& shader) {
	shader.setUniform1i(uniforName, m_value);
}
template <>
void UniformValueConcrete<float>::set(const std::string& uniforName, Shader& shader) {
	shader.setUniform1f(uniforName, m_value);
}
template <>
void UniformValueConcrete<glm::vec2>::set(const std::string& uniforName, Shader& shader) {
	shader.setUniform2f(uniforName, m_value);
}
template <>
void UniformValueConcrete<glm::vec3>::set(const std::string& uniforName, Shader& shader) {
	shader.setUniform3f(uniforName, m_value);
}
template <>
void UniformValueConcrete<glm::vec4>::set(const std::string& uniforName, Shader& shader) {
	shader.setUniform4f(uniforName, m_value);
}
template <>
void UniformValueConcrete<glm::mat4>::set(const std::string& uniforName, Shader& shader) {
	shader.setUniformMat4f(uniforName, m_value);
}