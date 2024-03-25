#include "ShaderLibrary.hpp"

size_t ShaderLibrary::LoadShader(const std::string& vertexFilepath, const std::string& fragmentFilepath, bool bCompileShader, const std::vector<std::string>& lookForInFS, const std::vector<std::string>& replaceWithInFS, const std::vector<std::string>& lookForInVS, const std::vector<std::string>& replaceWithInVS)
{
    m_shaders.emplace_back(vertexFilepath, fragmentFilepath, bCompileShader, lookForInFS, replaceWithInFS, lookForInVS, replaceWithInVS);
    m_listsTheShaderSubscribedTo.emplace_back();
    return m_shaders.size() - 1;
}

void ShaderLibrary::ReloadShader(size_t shaderLID, const std::vector<std::string>& lookForInFS, const std::vector<std::string>& replaceWithInFS, const std::vector<std::string>& lookForInVS, const std::vector<std::string>& replaceWithInVS)
{
    (*this)[shaderLID].compile(lookForInFS, replaceWithInFS, lookForInVS, replaceWithInVS);
    // Re-send uniforms
    for (UniformList list : m_listsTheShaderSubscribedTo[shaderLID])
        uniformList(list).sendUniformsTo(shaderLID);
}

void ShaderLibrary::addSubscriberToList(size_t shaderLID, UniformList list)
{
    uniformList(list).addSubscriber(shaderLID);
    m_listsTheShaderSubscribedTo[shaderLID].push_back(list);
}

UniformUpdateList& ShaderLibrary::uniformList(UniformList list)
{
    return m_uniformLists[(int)list];
}