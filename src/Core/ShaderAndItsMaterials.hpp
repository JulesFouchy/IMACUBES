#pragma once

#include "OpenGL/Shader.hpp"
#include "OpenGL/CubesGroup.hpp"

//#include "Types/UniformsStruct.hpp"
#include "Types/ArrayOfStructOfUniforms.hpp"

#include <string>

class ShaderAndItsMaterials {
public:
	ShaderAndItsMaterials(const std::string& vertexFilepath, const std::string& fragmentFilepath);
	~ShaderAndItsMaterials();

	void draw();

private:
	void setUniforms();

	void parseShader(const std::string& fragmentFilepath);
public:
	Shader m_shader;
	CubesGroup m_cubes;
	ArrayOfStructOfUniforms m_uniforms;
};