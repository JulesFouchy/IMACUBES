#pragma once

#include "Shader.hpp"
#include "Uniform/UniformUpdateList.hpp"

#include <vector>
#include <array>

enum class UniformList {
	Camera,
	Lights,
	SSAO,
	__size // must always be last (trick to get the number of UniformLists defined)
};

constexpr size_t __NbOfUniformLists__ = (size_t)UniformList::__size; // otherwise (size_t)UniformList::__size is still 0 when evalutaing templates (i.e. std::array<std::vector<UniformList>, (size_t)UniformList::__size>

class ShaderLibrary {
public:
	ShaderLibrary() = default;
	~ShaderLibrary() = default;

	size_t LoadShader(const std::string& vertexFilepath, const std::string& fragmentFilepath, bool bCompileShader = true, const std::vector<std::string>& lookForInFS = {}, const std::vector<std::string>& replaceWithInFS = {}, const std::vector<std::string>& lookForInVS = {}, const std::vector<std::string>& replaceWithInVS = {});
	void ReloadShader(size_t shaderLID, const std::vector<std::string>& lookForInFS = {}, const std::vector<std::string>& replaceWithInFS = {}, const std::vector<std::string>& lookForInVS = {}, const std::vector<std::string>& replaceWithInVS = {});
	inline Shader& operator[](size_t index) { return m_shaders[index]; }

	void addSubscriberToList(size_t shaderLID, UniformList list);
	UniformUpdateList& uniformList(UniformList list); // Do not use this to subscribe to a list ! Use "addSubscriberToList(shaderLID, list)" instead !

private:
	std::vector<Shader> m_shaders;
	std::vector<std::vector<UniformList>> m_listsTheShaderSubscribedTo;
	std::array<UniformUpdateList, __NbOfUniformLists__> m_uniformLists;
};