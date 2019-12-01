#pragma once

#include "OpenGL/Shader.hpp"
#include "OpenGL/CubesGroup.hpp"

#include "OpenGL/Uniform/ArrayOfStructOfUniforms.hpp"

#include <string>

class ShaderAndItsMaterials {
friend class MaterialsManager;
public:
	ShaderAndItsMaterials(const std::string& vertexFilepath, const std::string& fragmentFilepath, int shaderIndex);
	~ShaderAndItsMaterials();

	void draw();

	void reloadShader();

	void ImGui_Menu();

private:
	void setUniforms();

	void parseShader(const std::string& fragmentFilepath);
public:
	Shader m_shader;
	CubesGroup m_cubes;
	ArrayOfStructOfUniforms m_uniforms;

	std::string m_name;
	int m_shaderIndex;
};