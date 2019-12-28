#include "MaterialsManager.hpp"

#include "Locator/Locate.hpp"

#include "GUI/FileBrowser.hpp"
#include "Helper/File.hpp"

#include "imgui/misc/cpp/imgui_stdlib.h"

MaterialsManager::MaterialsManager()
	: m_shaderCount(0), m_selectedShaderID(0)
{
}

void MaterialsManager::draw() {
	for (MaterialsForAGivenShader& shader : m_shadersList) {
		shader.draw();
	}
}

void MaterialsManager::ImGui_ListOfShadersAndMaterials() {
	ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
	if (ImGui::BeginTabBar("MaterialsTabBar", tab_bar_flags))
	{
		int k = 0;
		for (MaterialsForAGivenShader& shader : m_shadersList) {
			if (ImGui::BeginTabItem(shader.m_name.c_str()))
			{
				ImGui::BeginChild("Child window---", ImVec2(ImGui::GetWindowContentRegionWidth(), ImGui::GetWindowHeight() * 0.30));
					shader.ImGui_ListOfMaterials();
				ImGui::EndChild();
				m_selectedShaderID = k;
				ImGui::EndTabItem();
			}
			k++;
		}
		ImGui::EndTabBar();
	}
}

void MaterialsManager::ImGui_SelectedMaterialsParameters() {
	Material& mat = SelectedMaterial();
	ImGui::InputText("", mat.getNamePointer());
	mat.ImGui_Sliders();
}

void MaterialsManager::ImGui_AddShaderButton() {
	if (ImGui::Button("Add shader")) {
		addShader(MyFile::rootDir + "/res/shaders/_default.vert", FileBrowser::openfilename(" frag (*.frag)\0*.frag;*.FRAG\0All Files (*.*)\0*.*\0"));
	}
}

void MaterialsManager::ImGui_AddMaterialToSelectedShaderButton() {
	if (ImGui::Button("Add Material")) {
		SelectedShader().addMaterial();
	}
}

MaterialLocation MaterialsManager::addCube(glm::vec3 pos, bool bPushActionInHistory) {
	if (bPushActionInHistory) {
		glm::vec3 _pos = pos;
		int _shaderID = m_selectedShaderID;
		int _materialID = m_selectedMaterialIDforThisShaderID[m_selectedShaderID];
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
	Shaders()[m_selectedShaderID].m_cubes.addCube(m_selectedMaterialIDforThisShaderID[m_selectedShaderID], pos);
	return SelectedMaterialLocation();
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
	if (fragmentFilepath.compare("")) {
		m_shadersList.emplace_back(vertexFilepath, fragmentFilepath, m_shaderCount++);
		m_selectedMaterialIDforThisShaderID[(int)m_shadersList.size() - 1] = 0;
	}
}