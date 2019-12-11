#include "MaterialsForAGivenShader.hpp"

#include <fstream>
#include "Helper/String.hpp"

#include "Debugging/Log.hpp"
#include "OpenGL/Uniform/UniformDescriptionFactory.hpp"

#include "imgui/misc/cpp/imgui_stdlib.h"

#include "Locator/MaterialManagerLocator.hpp"

MaterialsForAGivenShader::MaterialsForAGivenShader(const std::string& vertexFilepath, const std::string& fragmentFilepath, int shaderIndex)
	: m_shader(vertexFilepath, fragmentFilepath), m_cubes(), m_name(MyString::RemoveFileExtension(MyString::RemoveFolderHierarchy(fragmentFilepath))), m_shaderIndex(shaderIndex)
{
	parseShaderAndCreateUniformDescriptions(fragmentFilepath);
	addMaterial();
}

MaterialsForAGivenShader::MaterialsForAGivenShader(const MaterialsForAGivenShader& other)
	: m_shader(other.m_shader), m_cubes(other.m_cubes), m_materials(other.m_materials), m_name(other.m_name), m_shaderIndex(other.m_shaderIndex)
{
	for (UniformDescription* ptr : other.m_structLayout) {
		m_structLayout.push_back(ptr->createPtrWithSameData());
	}
}

MaterialsForAGivenShader::~MaterialsForAGivenShader() {
	for (UniformDescription* ptr : m_structLayout)
		delete ptr;
}

void MaterialsForAGivenShader::draw() {
	m_shader.bind();
	setUniforms(); // TODO only update uniform on material change
	m_cubes.draw();
}

void MaterialsForAGivenShader::addMaterial() {
	m_materials.emplace_back(MyString::RemoveFileExtension(MyString::RemoveFolderHierarchy(m_shader.getFragmentFilepath())) + std::to_string(m_materials.size()), m_structLayout, m_shaderIndex, (int)m_materials.size());
}

void MaterialsForAGivenShader::reloadShader() {
	m_shader.compile();
	parseShaderAndCreateUniformDescriptions(m_shader.getFragmentFilepath());
	updateMaterialsLayout();
}

void MaterialsForAGivenShader::ImGui_Menu(){
	ImGui::PushID((int)this);
		// Shader name
		ImGui::TextColored(ImVec4(54/255.0f, 158 / 255.0f, 61 / 255.0f,1.0), m_name.c_str());
		// Add material
		if (ImGui::Button("Add Material")) {
			addMaterial();
		}
		// Materials GUI
		for (Material& mat : m_materials) {
			ImGui::PushID((int)&mat);
			// Sliders of selected material
			if (Locate::materialsManager().SelectedMaterial().materialID == mat.getIndex() && Locate::materialsManager().SelectedMaterial().shaderID == m_shaderIndex) {
				ImGui::InputText("", mat.getNamePointer());
				mat.ImGui_Sliders();
			}
			// Name of other materials
			else {
				if (ImGui::Selectable(mat.getName().c_str(), false)) {
					Locate::materialsManager().SetSelectedMaterial(m_shaderIndex, mat.getIndex());
				}
			}
			//
			ImGui::Separator();
			ImGui::PopID();
		}
	//
	ImGui::PopID();
}

void MaterialsForAGivenShader::setUniforms() {
	for (Material& mat : m_materials) {
		mat.setUniforms();
	}
}


void MaterialsForAGivenShader::parseShaderAndCreateUniformDescriptions(const std::string& fragmentFilepath) {
	std::ifstream file(fragmentFilepath);
	if (file.is_open()) {
		m_structLayout.clear();
		std::string line;
		while (std::getline(file, line)) {
			// Look for 'struct MaterialParameters'
			if (line.find("struct MaterialParameters") != std::string::npos) { // TODO check that the line isn't commented out
				std::getline(file, line);
				while (line.find("}") == std::string::npos) {
					m_structLayout.push_back(UniformDescriptionFactory::FromShaderLine(line));
					// Go to next line
					std::getline(file, line);
				}
			}
		}
	}
	else {
		spdlog::warn("[MaterialsForAGivenShader::parseShaderAndCreateUniformDescriptions] unable to open file : '{}'", fragmentFilepath);
	}
}

void MaterialsForAGivenShader::updateMaterialsLayout() {
	for (Material& mat : m_materials) {
		mat.updateLayout(m_structLayout);
	}
}