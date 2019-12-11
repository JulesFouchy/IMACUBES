#pragma once

#include "MaterialsForAGivenShader.hpp"
#include "MaterialLocation.hpp"
#include <vector>

#include "glm/glm.hpp"

class MaterialsManager {
public:
	MaterialsManager() = delete;
	~MaterialsManager() = delete;

	static void draw();
	static void ImGui_Menu();

	static inline void addShader(const std::string& vertexFilepath, const std::string& fragmentFilepath) { m_shadersList.emplace_back(vertexFilepath, fragmentFilepath, m_shaderCount++); }
	static void updateMatrixUniform(const std::string& name, const glm::mat4& mat);

	static inline std::vector<MaterialsForAGivenShader>& Shaders() { return m_shadersList; }
	static inline const MaterialLocation& SelectedMaterial() { return m_selectedMaterial; }
	static inline void SetSelectedMaterial(int shaderID, int matID) { m_selectedMaterial = { shaderID, matID }; }
private:
	static std::vector<MaterialsForAGivenShader> m_shadersList;
	static int m_shaderCount;

	static MaterialLocation m_selectedMaterial;
};