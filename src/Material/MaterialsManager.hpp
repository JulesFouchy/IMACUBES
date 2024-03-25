#pragma once

#include <unordered_map>
#include <vector>
#include "MaterialLocation.hpp"
#include "MaterialsForAGivenShader.hpp"
#include "glm/glm.hpp"

class MaterialsManager {
public:
    MaterialsManager();
    ~MaterialsManager() = default;

    void draw();
    void draw_WithoutBindingShaders();
    void ImGui_ListOfShadersAndMaterials();
    void ImGui_SelectedMaterialsParameters();
    void ImGui_AddShaderButton();
    void ImGui_AddMaterialToSelectedShaderButton(bool forcedPress = false);

    void addShader(const std::string& vertexFilepath, const std::string& fragmentFilepath);

    MaterialLocation addCube(const glm::ivec3& pos, bool bPushActionInHistory = true, HistoryType type = HistoryType::Cubes); // returns the location where the cube was added (i.e. m_selectedMaterialLocation)
    void             removeCube(int shaderID, const glm::ivec3& pos, bool bPushActionInHistory = true, HistoryType type = HistoryType::Cubes);

    inline std::vector<MaterialsForAGivenShader>& Shaders() { return m_shadersList; }
    inline const MaterialLocation                 SelectedMaterialLocation() { return MaterialLocation(m_selectedShaderID, m_selectedMaterialIDforThisShaderID[m_selectedShaderID]); }

    void setSelectedMaterial(int shaderID, int matID);

    inline MaterialsForAGivenShader& SelectedShader() { return Shaders()[SelectedMaterialLocation().shaderID]; }
    inline Material&                 SelectedMaterial() { return SelectedShader().m_materials[SelectedMaterialLocation().materialID]; }

private:
    std::vector<MaterialsForAGivenShader> m_shadersList;
    int                                   m_shaderCount;

    int                          m_selectedShaderID;
    std::unordered_map<int, int> m_selectedMaterialIDforThisShaderID;
    bool                         m_bSelectedShaderJustChanged;
};