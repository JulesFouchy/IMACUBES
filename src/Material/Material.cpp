#include "Material.hpp"
#include "Debugging/Log.hpp"
#include "MaterialsLocator.hpp"
#include "OpenGL/Uniform/Uniform.hpp"

Material::Material(const std::string& name, const std::vector<UniformDescription*>& structLayout, int shaderIndex, int materialIndex)
    : m_shaderIndex(shaderIndex), m_materialIndex(materialIndex), m_name(name)
{
    updateLayout(structLayout);
    m_lightingProperties.push_back(new Uniform<float>("Specular_strength", HistoryType::Materials, 0.0f, 0.0f, 4.0f));
    m_lightingProperties.push_back(new Uniform<float>("Shininess", HistoryType::Materials, 32.0f, 1.0f, 128.0f));
}

Material::Material(const Material& other)
    : m_shaderIndex(other.m_shaderIndex), m_materialIndex(other.m_materialIndex), m_name(other.m_name)
{
    for (UniformAbstract* uni : other.m_uniformsStruct)
        m_uniformsStruct.push_back(uni->createPtrWithSameData());
    for (UniformAbstract* uni : other.m_lightingProperties)
        m_lightingProperties.push_back(uni->createPtrWithSameData());
}

Material::~Material()
{
    for (UniformAbstract* ptr : m_uniformsStruct)
    {
        delete ptr;
    }
    for (UniformAbstract* ptr : m_lightingProperties)
    {
        delete ptr;
    }
}

void Material::updateLayout(const std::vector<UniformDescription*>& structLayout)
{
    for (UniformDescription* uniDescription : structLayout)
    {
        int uniIndex = findUniform(uniDescription->name);
        if (uniIndex == -1)
        {
            addUniformToStruct(uniDescription);
        }
        else
        {
            updateUniformInsideStruct(uniIndex, uniDescription);
        }
    }
}

void Material::sendUniforms()
{
    for (UniformAbstract* uni : m_uniformsStruct)
    {
        uni->sendTo(MaterialsLocator::GetShader(m_shaderIndex), uniformParamsName(uni->getName()));
    }
    for (UniformAbstract* uni : m_lightingProperties)
    {
        uni->sendTo(MaterialsLocator::GetShader(m_shaderIndex), uniformLightPropName(uni->getName()));
    }
}

void Material::ImGui_Sliders()
{
    for (UniformAbstract* uni : m_uniformsStruct)
    {
        uni->ImGui_Slider();
    }
    ImGui::Separator();
    for (UniformAbstract* uni : m_lightingProperties)
    {
        uni->ImGui_Slider();
    }
}

int Material::findUniform(const std::string& name)
{
    for (int k = 0; k < m_uniformsStruct.size(); ++k)
    {
        if (!m_uniformsStruct[k]->getName().compare(name))
            return k;
    }
    return -1;
}

void Material::addUniformToStruct(UniformDescription* uniformDescription)
{
    m_uniformsStruct.push_back(uniformDescription->createUniformPtr());
}

void Material::updateUniformInsideStruct(int uniformIndex, UniformDescription* uniformDescription)
{
    uniformDescription->updateThisUniform(m_uniformsStruct[uniformIndex]);
}