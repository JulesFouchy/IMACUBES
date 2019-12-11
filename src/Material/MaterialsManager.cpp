#include "MaterialsManager.hpp"

MaterialsManager::MaterialsManager()
	: m_shaderCount(0), m_selectedMaterial(0, 0)
{}

void MaterialsManager::draw() {
	for (MaterialsForAGivenShader& shader : m_shadersList) {
		shader.draw();
	}
}

void MaterialsManager::ImGui_Menu() {
	ImGui::Begin("Materials");
	for (MaterialsForAGivenShader& shader : m_shadersList) {
		shader.ImGui_Menu();
	}
	ImGui::End();
}

void MaterialsManager::updateMatrixUniform(const std::string& name, const glm::mat4& mat) {
	for (MaterialsForAGivenShader& shader : m_shadersList) {
		shader.m_shader.bind();
		shader.m_shader.setUniformMat4f(name, mat);
	}
}