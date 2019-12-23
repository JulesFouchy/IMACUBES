#pragma once

#include "OpenGL/Shader.hpp"
#include "OpenGL/CubesGroup.hpp"
#include "OpenGL/Uniform/UniformDescription.hpp"

#include "Material/Material.hpp"

#include <string>

class MaterialsForAGivenShader {
friend class MaterialsManager;
public:
	MaterialsForAGivenShader(const std::string& vertexFilepath, const std::string& fragmentFilepath, int shaderIndex);
	MaterialsForAGivenShader(const MaterialsForAGivenShader& other);
	MaterialsForAGivenShader(MaterialsForAGivenShader&& other) noexcept;
	~MaterialsForAGivenShader();

	void draw();
	void addMaterial();

	void reloadShader();

	void ImGui_Menu();

	Shader& shader();

private:
	void setUniforms();

	void parseShaderAndCreateUniformDescriptions(const std::string& fragmentFilepath);
	void updateMaterialsLayout();
private:
	size_t m_shaderLID;
	CubesGroup m_cubes;
	std::vector<UniformDescription*> m_structLayout;
	std::vector<Material> m_materials;

	std::string m_name;
	int m_shaderIndex;
};