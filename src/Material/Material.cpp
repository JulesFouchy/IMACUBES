#include "Material.hpp"

#include "Debugging/Log.hpp"

Material::Material(const std::string& name, const std::vector<UniformDescription*>& structLayout, int shaderIndex, int materialIndex)
	: m_shaderIndex(shaderIndex), m_materialIndex(materialIndex), m_name(name)
{
	updateLayout(structLayout);
}

Material::Material(const Material& other)
	: m_shaderIndex(other.m_shaderIndex), m_materialIndex(other.m_materialIndex), m_name(other.m_name)
{
	for (Uniform_ForMaterialSystem* uni : other.m_uniformsStruct)
		m_uniformsStruct.push_back(uni->createPtrWithSameData());
}

Material::~Material() {
	for (Uniform_ForMaterialSystem* ptr : m_uniformsStruct) {
		delete ptr;
	}
}

void Material::updateLayout(const std::vector<UniformDescription*>& structLayout) {
	for (UniformDescription* uniDescription : structLayout) {
		int uniIndex = findUniform(uniDescription->name);
		if (uniIndex == -1) {
			addUniformToStruct(uniDescription);
		}
		else {
			updateUniformInsideStruct(uniIndex, uniDescription);
		}
	}
}

void Material::setUniforms() {
	for (Uniform_ForMaterialSystem* uni : m_uniformsStruct) {
		uni->set(m_materialIndex);
	}
}

void Material::ImGui_Sliders() {
	for (Uniform_ForMaterialSystem* uni : m_uniformsStruct) {
		uni->ImGui_Slider();
	}
}

int Material::findUniform(const std::string& name) {
	for (int k = 0; k < m_uniformsStruct.size(); ++k) {
		if (!m_uniformsStruct[k]->getNameInsideStruct().compare(name))
			return k;
	}
	return -1;
}

void Material::addUniformToStruct(UniformDescription* uniformDescription) {
	m_uniformsStruct.push_back(uniformDescription->createUniformPtr(m_shaderIndex));
}

void Material::updateUniformInsideStruct(int uniformIndex, UniformDescription* uniformDescription) {
	uniformDescription->updateThisUniform(m_uniformsStruct[uniformIndex]);
}