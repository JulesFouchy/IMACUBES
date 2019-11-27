#include "ArrayOfStructOfUniforms.hpp"

#include "imgui.h"

#include "Debugging/Log.hpp"

ArrayOfStructOfUniforms::ArrayOfStructOfUniforms() {

}

void ArrayOfStructOfUniforms::set() {
	for (int k = 0; k < m_structOfUniforms.size(); ++k) {
		StructOfUniforms& uniStruct = m_structOfUniforms[k];
		for (Uniform* uni : uniStruct) {
			uni->set();
		}
	}
}

void ArrayOfStructOfUniforms::addStruct(){
	m_structOfUniforms.resize(m_structOfUniforms.size() + 1);
}

void ArrayOfStructOfUniforms::addUniform(Uniform* uniform) {
	for (StructOfUniforms& structUni : m_structOfUniforms) {
		Uniform* ptr = uniform->createPtrWithSameData();
		spdlog::info((int)ptr);
		structUni.push_back(ptr);
	}
}

void ArrayOfStructOfUniforms::ImGui_Sliders() {
	ImGui::Begin("Mats");
	for (StructOfUniforms unis : m_structOfUniforms) {
		for (Uniform* uni : unis) {
			uni->ImGui_Slider();
		}
	}
	ImGui::End();
}