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
	void ImGui_ListOfShadersAndMaterials();
	void ImGui_SelectedMaterialsParameters();

	void addShader(const std::string& vertexFilepath, const std::string& fragmentFilepath);

	MaterialLocation addCube(glm::vec3 pos, bool bPushActionInHistory = true); // returns the location where the cube was added (i.e. m_selectedMaterialLocation)
	void removeCube(int shaderID, glm::vec3 pos, bool bPushActionInHistory = true);

	inline std::vector<MaterialsForAGivenShader>& Shaders() { return m_shadersList; }
	inline const MaterialLocation& SelectedMaterialLocation() { return m_selectedMaterialLocation; }
	
	inline void SetSelectedMaterial(int shaderID, int matID) { m_selectedMaterialLocation = { shaderID, matID }; }
private:
	inline Material& SelectedMaterial() { return Shaders()[SelectedMaterialLocation().shaderID].m_materials[SelectedMaterialLocation().materialID]; }
private:
	std::vector<MaterialsForAGivenShader> m_shadersList;
	int m_shaderCount;

	MaterialLocation m_selectedMaterialLocation;
};