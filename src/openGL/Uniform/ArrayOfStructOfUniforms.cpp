#include "ArrayOfStructOfUniforms.hpp"

#include "imgui.h"

#include "Debugging/Log.hpp"

void ArrayOfStructOfUniforms::deleteAllPointers() {
	for (StructOfUniforms uniStruct : m_structsOfUniforms) {
		for (Uniform* uniPtr : uniStruct)
			delete uniPtr;
	}
}

void ArrayOfStructOfUniforms::setUniforms() {
	for (StructOfUniforms& uniStruct : m_structsOfUniforms) {
		for (Uniform* uni : uniStruct) {
			uni->set();
		}
	}
}

void ArrayOfStructOfUniforms::addStruct(){
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
}

void ArrayOfStructOfUniforms::ImGui_Sliders(const std::string& windowName) {
	ImGui::Begin(windowName.c_str());
	for (StructOfUniforms uniStruct : m_structsOfUniforms) {
		for (Uniform* uni : uniStruct) {
			uni->ImGui_Slider();
		}
		ImGui::Separator();
	}
	ImGui::End();
}

int ArrayOfStructOfUniforms::find(const std::string& uniformName) {
	for (int k = 0; k < m_structsOfUniforms[0].size(); ++k) {
		if (m_structsOfUniforms[0][k]->getName() == uniformName)
			return k;
	}
	return -1;
}