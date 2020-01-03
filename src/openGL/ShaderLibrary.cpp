#include "ShaderLibrary.hpp"

size_t ShaderLibrary::LoadShader(const std::string& vertexFilepath, const std::string& fragmentFilepath, bool bCompileShader) {
	m_shaders.emplace_back(vertexFilepath, fragmentFilepath, bCompileShader);
	return m_shaders.size() - 1;
}