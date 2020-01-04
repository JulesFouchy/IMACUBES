#include "MaterialsForAGivenShader.hpp"

#include <fstream>
#include "Helper/String.hpp"

#include "Debugging/Log.hpp"
#include "OpenGL/Uniform/UniformDescriptionFactory.hpp"

#include "Locator/Locate.hpp"
#include "OpenGL/Uniform/UniformUpdateList.hpp"
#include "MaterialsManager.hpp"

MaterialsForAGivenShader::MaterialsForAGivenShader(const std::string& vertexFilepath, const std::string& fragmentFilepath, int shaderIndex)
	: m_shaderLID(Locate::shaderLibrary().LoadShader(vertexFilepath, fragmentFilepath)), 
	  m_cubes(), m_name(MyString::RemoveFileExtension(MyString::RemoveFolderHierarchy(fragmentFilepath))), m_shaderIndex(shaderIndex)
{
	Locate::cameraUniforms().addSubscriber(m_shaderLID);
	parseShaderAndCreateUniformDescriptions(fragmentFilepath);
	addMaterial();
}

MaterialsForAGivenShader::MaterialsForAGivenShader(const MaterialsForAGivenShader& other)
	: m_shaderLID(other.m_shaderLID), m_cubes(other.m_cubes), m_materials(other.m_materials), m_name(other.m_name), m_shaderIndex(other.m_shaderIndex)
{
	for (UniformDescription* ptr : other.m_structLayout) {
		m_structLayout.push_back(ptr->createPtrWithSameData());
	}
}

MaterialsForAGivenShader::MaterialsForAGivenShader(MaterialsForAGivenShader&& other) noexcept
	: m_shaderLID(other.m_shaderLID), m_cubes(std::move(other.m_cubes)), m_materials(std::move(other.m_materials)), m_name(std::move(other.m_name)), m_shaderIndex(other.m_shaderIndex)
{
	for (UniformDescription*& ptr : other.m_structLayout) {
		m_structLayout.push_back(ptr);
		ptr = nullptr;
	}
}

MaterialsForAGivenShader::~MaterialsForAGivenShader() {
	for (UniformDescription* ptr : m_structLayout)
		delete ptr;
}

void MaterialsForAGivenShader::draw() {
	shader().bind();
	sendUniforms(); // TODO only update uniform on material change
	m_cubes.draw();
}

#include "Renderer/Renderer.hpp"
void MaterialsForAGivenShader::addMaterial() {
	m_materials.emplace_back(MyString::RemoveFileExtension(MyString::RemoveFolderHierarchy(shader().getFragmentFilepath())) + std::to_string(m_materials.size()), m_structLayout, m_shaderIndex, (int)m_materials.size());
	Locate::materialsManager().setSelectedMaterial(m_shaderIndex, (int)m_materials.size() - 1);
	shader().compile("DEFINE_ME_nbOfMaterials", std::to_string(m_materials.size()));
	Locate::renderer().cameraUniforms().sendUniformsTo(m_shaderLID);
}

void MaterialsForAGivenShader::reloadShader() {
	shader().compile();
	parseShaderAndCreateUniformDescriptions(shader().getFragmentFilepath());
	updateMaterialsLayout();
}

Shader& MaterialsForAGivenShader::shader() {
	return Locate::shaderLibrary()[m_shaderLID];
}

void MaterialsForAGivenShader::ImGui_ListOfMaterials(){
	// Materials GUI
	for (Material& mat : m_materials) {
		ImGui::PushID((int)&mat);
		bool isSelected = Locate::materialsManager().SelectedMaterialLocation().materialID == mat.getIndex() && Locate::materialsManager().SelectedMaterialLocation().shaderID == m_shaderIndex;
		// Name of other materials
		if (ImGui::Selectable(mat.getName().c_str(), isSelected)) {
			Locate::materialsManager().setSelectedMaterial(m_shaderIndex, mat.getIndex());
		}
		//
		ImGui::Separator();
		ImGui::PopID();
	}
}

void MaterialsForAGivenShader::sendUniforms() {
	for (Material& mat : m_materials) {
		mat.sendUniforms();
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
					m_structLayout.push_back(UniformDescriptionFactory::FromShaderLine(line, HistoryType::Materials));
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