#include "MaterialsManager.hpp"

#include "Locator/Locate.hpp"

#include "GUI/FileBrowser.hpp"
#include "Helper/File.hpp"

#include "imgui/misc/cpp/imgui_stdlib.h"

MaterialsManager::MaterialsManager()
	: m_shaderCount(0), m_selectedMaterialLocation(0, 0)
{
}

void MaterialsManager::draw() {
	for (MaterialsForAGivenShader& shader : m_shadersList) {
		shader.draw();
	}
}

void MaterialsManager::ImGui_ListOfShadersAndMaterials() {
	if (ImGui::Button("Add shader")) {
		addShader(MyFile::rootDir + "/res/shaders/_default.vert", FileBrowser::openfilename(" frag (*.frag)\0*.frag;*.FRAG\0All Files (*.*)\0*.*\0"));
	}
	for (MaterialsForAGivenShader& shader : m_shadersList) {
		shader.ImGui_ListOfMaterials();
	}
}

void MaterialsManager::ImGui_SelectedMaterialsParameters() {
	Material& mat = SelectedMaterial();
	ImGui::InputText("", mat.getNamePointer());
	mat.ImGui_Sliders();
}

MaterialLocation MaterialsManager::addCube(glm::vec3 pos, bool bPushActionInHistory) {
	if (bPushActionInHistory) {
		glm::vec3 _pos = pos;
		int _shaderID = m_selectedMaterialLocation.shaderID;
		int _materialID = m_selectedMaterialLocation.materialID;
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
	Shaders()[m_selectedMaterialLocation.shaderID].m_cubes.addCube(m_selectedMaterialLocation.materialID, pos);
	return m_selectedMaterialLocation;
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

void MaterialsManager::addShader(const std::string& vertexFilepath, const std::string& fragmentFilepath) {
	if(fragmentFilepath.compare(""))
		m_shadersList.emplace_back(vertexFilepath, fragmentFilepath, m_shaderCount++);
}