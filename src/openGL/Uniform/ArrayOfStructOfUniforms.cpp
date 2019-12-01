#include "ArrayOfStructOfUniforms.hpp"

#include "imgui.h"
#include "imgui/misc/cpp/imgui_stdlib.h"

#include "Debugging/Log.hpp"

#include "Core/MaterialsManager.hpp"


ArrayOfStructOfUniforms::ArrayOfStructOfUniforms(int shaderIndex)
	: m_shaderIndex(shaderIndex)
{

}

ArrayOfStructOfUniforms::ArrayOfStructOfUniforms(const ArrayOfStructOfUniforms& other)
	: m_structNames(other.m_structNames), m_shaderIndex(other.m_shaderIndex)
{
	m_structsOfUniforms.resize(other.m_structsOfUniforms.size());
	for (int k = 0; k < other.m_structsOfUniforms.size(); ++k) {
		m_structsOfUniforms[k].resize(other.m_structsOfUniforms[k].size());
		for (int i = 0; i < other.m_structsOfUniforms[k].size(); ++i) {
			m_structsOfUniforms[k][i] = other.m_structsOfUniforms[k][i]->createPtrWithSameData();
		}
	}
}

void ArrayOfStructOfUniforms::deleteAllPointers() {
	for (StructOfUniforms uniStruct : m_structsOfUniforms) {
		for (Uniform* uniPtr : uniStruct)
			delete uniPtr;
	}
}

void ArrayOfStructOfUniforms::setUniforms() {
	int structID = 0;
	for (StructOfUniforms& uniStruct : m_structsOfUniforms) {
		for (Uniform* uni : uniStruct) {
			uni->set(structID);
		}
		structID++;
	}
}

void ArrayOfStructOfUniforms::addStruct(const std::string& shaderName){
	m_structNames.push_back(shaderName + std::to_string(m_structNames.size()));
	m_structsOfUniforms.resize(m_structsOfUniforms.size() + 1);
	size_t size = m_structsOfUniforms.size();
	if (size > 1) {
		for (Uniform* uni : m_structsOfUniforms[size-2]) {
			m_structsOfUniforms[size-1].push_back(uni->createPtrWithSameData());
		}
	}
}

void ArrayOfStructOfUniforms::addUniform(Uniform* uniform) {
	for (StructOfUniforms& uniStruct : m_structsOfUniforms) {
		Uniform* ptr = uniform->createPtrWithSameData();
		uniStruct.push_back(ptr);
	}
	delete uniform;
}

void ArrayOfStructOfUniforms::ImGui_Sliders() {
	int k = 0;
	for (StructOfUniforms& uniStruct : m_structsOfUniforms) {
		ImGui::PushID((int)&uniStruct);

		if (MaterialsManager::SelectedMaterial().materialID == k && MaterialsManager::SelectedMaterial().shaderID == m_shaderIndex) {
			ImGui::Text("Mat "); ImGui::SameLine();
			ImGui::InputText("", &m_structNames[k]); ImGui::SameLine(); ImGui::Text(" :");
			for (Uniform* uni : uniStruct) {
				uni->ImGui_Slider();
			}
		}
		else {
			ImGui::Text("Mat"); ImGui::SameLine();
			ImGui::Text(m_structNames[k].c_str());
		}

		ImGui::Separator();
		ImGui::PopID();
		k++;
	}
}

int ArrayOfStructOfUniforms::find(const std::string& nameInsideStruct) {
	for (int k = 0; k < m_structsOfUniforms[0].size(); ++k) {
		if (!m_structsOfUniforms[0][k]->getNameInsideStruct().compare(nameInsideStruct))
			return k;
	}
	return -1;
}