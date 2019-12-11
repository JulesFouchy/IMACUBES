#pragma once

#include "MaterialsForAGivenShader.hpp"
#include "MaterialLocation.hpp"
#include <vector>

#include "glm/glm.hpp"

class MaterialsManager {
public:
	MaterialsManager();
	~MaterialsManager() = default;

	void draw();
	void ImGui_Menu();

	inline void addShader(const std::string& vertexFilepath, const std::string& fragmentFilepath) { m_shadersList.emplace_back(vertexFilepath, fragmentFilepath, m_shaderCount++); }
	void updateMatrixUniform(const std::string& name, const glm::mat4& mat);

	inline std::vector<MaterialsForAGivenShader>& Shaders() { return m_shadersList; }
	inline const MaterialLocation& SelectedMaterial() { return m_selectedMaterial; }
	inline void SetSelectedMaterial(int shaderID, int matID) { m_selectedMaterial = { shaderID, matID }; }
private:
	std::vector<MaterialsForAGivenShader> m_shadersList;
	int m_shaderCount;

	MaterialLocation m_selectedMaterial;
};