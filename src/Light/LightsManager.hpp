#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "DirectionalLight.hpp"
#include "Light.hpp"
#include "LightTypes.hpp"
#include "OpenGL/Uniform/UniformUpdateList.hpp"
#include "PointLight.hpp"

class LightsManager {
public:
    LightsManager();
    ~LightsManager() = default;
    void initAfterApp();

    void addPointLight(const glm::vec3& position, const glm::vec3& color = glm::vec3(1.0f), float intensity = 5.0f);
    void addDirectionalLight(float angleUp, float angleGround, const glm::vec3& color = glm::vec3(1.0f), float intensity = 1.0f);
    void duplicateSelectedPointLight();
    void duplicateSelectedDirectionalLight();

    void computeShadowMaps();
    void attachAndSendShadowMaps(Shader& shader);
    void detachShadowMaps();
    void ImGui_ShadowParameters();

    void setUniforms(UniformUpdateList& list);

    void ImGui_LightsList();
    void ImGui_SelectedLightSliders();
    void ImGui_AddLightOfSelectedTypeButton(bool forcedPress = false);

    Light* selectedLight();
    void   trySetSelectedPointLightPosition(const glm::vec3& position);

    inline DirectionalLight& selectedDirectionalLight() { return m_directionalLights[m_selectedDirectionalIndex]; }

private:
    void updateNbOfLightsInShaders();

private:
    LightType m_selectedLightType;
    int       m_selectedPointIndex;
    int       m_selectedDirectionalIndex;

    Light                         m_ambiantLight;
    std::vector<PointLight>       m_pointLights;
    std::vector<DirectionalLight> m_directionalLights;
};