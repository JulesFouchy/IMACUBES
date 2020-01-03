#pragma once

#include "Shader.hpp"

#include <vector>

class ShaderLibrary {
public:
	ShaderLibrary() = default;
	~ShaderLibrary() = default;

	size_t LoadShader(const std::string& vertexFilepath, const std::string& fragmentFilepath, bool bCompileShader = true);
	inline Shader& operator[](size_t index) { return m_shaders[index]; }

private:
	std::vector<Shader> m_shaders;
};