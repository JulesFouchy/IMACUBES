#include "MaterialsManager.hpp"
#include <imgui/imgui.h>
#include "GUI/FileBrowser.hpp"
#include "Helper/File.hpp"
#include "History/History.hpp"
#include "Locator/Locate.hpp"
#include "imgui/misc/cpp/imgui_stdlib.h"

MaterialsManager::MaterialsManager()
    : m_shaderCount(0), m_selectedShaderID(0), m_bSelectedShaderJustChanged(false)
{
}

void MaterialsManager::draw()
{
    for (MaterialsForAGivenShader& shader : m_shadersList)
    {
        shader.draw();
    }
}

void MaterialsManager::draw_WithoutBindingShaders()
{
    for (MaterialsForAGivenShader& shader : m_shadersList)
    {
        shader.draw_WithoutBindingShader();
    }
}

void MaterialsManager::ImGui_ListOfShadersAndMaterials()
{
    ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
    if (ImGui::BeginTabBar("MaterialsTabBar", tab_bar_flags))
    {
        int k = 0;
        for (MaterialsForAGivenShader& shader : m_shadersList)
        {
            ImGuiTabItemFlags itemFlags = (m_bSelectedShaderJustChanged && m_selectedShaderID == k) ? ImGuiTabItemFlags_SetSelected : ImGuiTabItemFlags_None;
            if (ImGui::BeginTabItem(shader.m_name.c_str(), nullptr, itemFlags))
            {
                ImGui::BeginChild("Child window---", ImVec2(ImGui::GetWindowContentRegionWidth(), ImGui::GetWindowHeight() * 0.30));
                shader.ImGui_ListOfMaterials();
                ImGui::EndChild();
                if (!m_bSelectedShaderJustChanged)
                    m_selectedShaderID = k;
                ImGui::EndTabItem();
            }
            k++;
        }
        m_bSelectedShaderJustChanged = false;
        ImGui::EndTabBar();
    }
}

void MaterialsManager::ImGui_SelectedMaterialsParameters()
{
    Material& mat = SelectedMaterial();
    ImGui::InputText("", mat.getNamePointer());
    mat.ImGui_Sliders();
}

void MaterialsManager::ImGui_AddShaderButton()
{
    if (ImGui::Button("Add shader"))
    {
        addShader(MyFile::rootDir + "/res/shaders/_geometryPass.vert", FileBrowser::openfilename(" frag (*.frag)\0*.frag;*.FRAG\0All Files (*.*)\0*.*\0"));
    }
}

void MaterialsManager::ImGui_AddMaterialToSelectedShaderButton(bool forcedPress)
{
    if (ImGui::Button("Add Material") || forcedPress)
    {
        SelectedShader().addMaterial();
    }
}

MaterialLocation MaterialsManager::addCube(const glm::ivec3& pos, bool bPushActionInHistory, HistoryType type)
{
    if (bPushActionInHistory)
    {
        glm::vec3 _pos        = pos;
        int       _shaderID   = m_selectedShaderID;
        int       _materialID = m_selectedMaterialIDforThisShaderID[m_selectedShaderID];
        Locate::history(type).addAction(Action(
            // DO action
            [this, _pos, _shaderID, _materialID]() {
                this->Shaders()[_shaderID].m_cubes.addCube(_materialID, _pos);
            },
            // UNDO action
            [this, _pos, _shaderID]() {
                this->removeCube(_shaderID, _pos, false);
            }
        ));
    }
    Shaders()[m_selectedShaderID].m_cubes.addCube(m_selectedMaterialIDforThisShaderID[m_selectedShaderID], pos);
    return SelectedMaterialLocation();
}

void MaterialsManager::removeCube(int shaderID, const glm::ivec3& pos, bool bPushActionInHistory, HistoryType type)
{
    if (bPushActionInHistory)
    {
        int        _shaderID   = shaderID;
        int        _materialID = Shaders()[shaderID].m_cubes.getCubeMaterialID(pos);
        glm::ivec3 _pos        = pos;
        Locate::history(type).addAction(Action(
            // DO action
            [this, _shaderID, _pos]() {
                this->removeCube(_shaderID, _pos, false);
            },
            // UNDO action
            [this, _pos, _shaderID, _materialID]() {
                this->Shaders()[_shaderID].m_cubes.addCube(_materialID, _pos);
            }
        ));
    }
    Shaders()[shaderID].m_cubes.removeCube(pos);
}

void MaterialsManager::addShader(const std::string& vertexFilepath, const std::string& fragmentFilepath)
{
    if (fragmentFilepath.compare(""))
    {
        m_shadersList.emplace_back(vertexFilepath, fragmentFilepath, m_shaderCount++);
        m_selectedMaterialIDforThisShaderID[(int)m_shadersList.size() - 1] = 0;
    }
}

void MaterialsManager::setSelectedMaterial(int shaderID, int matID)
{
    m_selectedShaderID                            = shaderID;
    m_selectedMaterialIDforThisShaderID[shaderID] = matID;
    m_bSelectedShaderJustChanged                  = true;
}