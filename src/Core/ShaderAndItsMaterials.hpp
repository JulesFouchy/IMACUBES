#pragma once

#include "OpenGL/Shader.hpp"
#include "OpenGL/CubesGroup.hpp"

#include <string>

class ShaderAndItsMaterials {
public:
	ShaderAndItsMaterials(const std::string& vertexFilepath, const std::string& fragmentFilepath);
	~ShaderAndItsMaterials();

	void draw();
private:
	Shader m_shader;
	CubesGroup m_cubes;
};