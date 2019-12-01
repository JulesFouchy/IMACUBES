#include "MaterialsManager.hpp"

std::vector<ShaderAndItsMaterials> MaterialsManager::m_shadersList;
int MaterialsManager::m_shaderCount = 0;

void MaterialsManager::draw() {
	for (ShaderAndItsMaterials& shader : m_shadersList) {
		shader.draw();
	}
}

void MaterialsManager::ImGui_Menu() {
	ImGui::Begin("Materials");
	for (ShaderAndItsMaterials& shader : m_shadersList) {
		shader.ImGui_Menu();
	}
	ImGui::End();
}

void MaterialsManager::updateMatrixUniform(const std::string& name, const glm::mat4& mat) {
	for (ShaderAndItsMaterials& shader : m_shadersList) {
		shader.m_shader.bind();
		shader.m_shader.setUniformMat4f(name, mat);
	}
}