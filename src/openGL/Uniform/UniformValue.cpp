#include "UniformValue.hpp"

template <>
void UniformValueConcrete<int>::set(const std::string& uniformName, Shader& shader) {
	shader.setUniform1i(uniformName, m_value);
}
template <>
void UniformValueConcrete<float>::set(const std::string& uniformName, Shader& shader) {
	shader.setUniform1f(uniformName, m_value);
}
template <>
void UniformValueConcrete<glm::vec2>::set(const std::string& uniformName, Shader& shader) {
	shader.setUniform2f(uniformName, m_value);
}
template <>
void UniformValueConcrete<glm::vec3>::set(const std::string& uniformName, Shader& shader) {
	shader.setUniform3f(uniformName, m_value);
}
template <>
void UniformValueConcrete<glm::vec4>::set(const std::string& uniformName, Shader& shader) {
	shader.setUniform4f(uniformName, m_value);
}
template <>
void UniformValueConcrete<glm::mat4>::set(const std::string& uniformName, Shader& shader) {
	shader.setUniformMat4f(uniformName, m_value);
}