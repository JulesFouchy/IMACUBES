#include "MaterialsManager.hpp"

#include "Locator/Locate.hpp"

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

MaterialLocation MaterialsManager::addCube(glm::vec3 pos, bool bPushActionInHistory) {
	if (bPushActionInHistory) {
		glm::vec3 _pos = pos;
		int _shaderID = m_selectedMaterial.shaderID;
		int _materialID = m_selectedMaterial.materialID;
		Locate::history(HistoryType::Cubes).addAction(Action(
			// DO action
			[this, _pos, _shaderID, _materialID]()
		{
			this->Shaders()[_shaderID].m_cubes.addCube(_materialID, _pos);
		},
			// UNDO action
			[this, _pos, _shaderID]()
		{
			this->removeCube(_shaderID, _pos, false);
		}
		));
	}
	Shaders()[m_selectedMaterial.shaderID].m_cubes.addCube(m_selectedMaterial.materialID, pos);
	return m_selectedMaterial;
}

void MaterialsManager::removeCube(int shaderID, glm::vec3 pos, bool bPushActionInHistory) {
	if (bPushActionInHistory) {
		int _shaderID = shaderID;
		int _materialID = Shaders()[shaderID].m_cubes.getCubeMaterialID(pos);
		glm::vec3 _pos = pos;
		Locate::history(HistoryType::Cubes).addAction(Action(
			// DO action
			[this, _shaderID, _pos]()
		{
			this->removeCube(_shaderID, _pos, false);
		},
			// UNDO action
			[this, _pos, _shaderID, _materialID]()
		{
			this->Shaders()[_shaderID].m_cubes.addCube(_materialID, _pos);
		}
		));
	}
	Shaders()[shaderID].m_cubes.removeCube(pos);
}