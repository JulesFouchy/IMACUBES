#include "ShaderLibrary.hpp"

size_t ShaderLibrary::LoadShader(const std::string& vertexFilepath, const std::string& fragmentFilepath) {
	m_shaders.emplace_back(vertexFilepath, fragmentFilepath);
	return m_shaders.size() - 1;
}