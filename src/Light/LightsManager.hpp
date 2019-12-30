#pragma once

#include "Light.hpp"
#include "PointLight.hpp"
#include "DirectionalLight.hpp"

#include "OpenGL/Uniform/UniformUpdateList.hpp"

#include <vector>
#include <glm/glm.hpp>

enum class LightType {
	Ambiant,
	Point,
	Directional
};

class LightsManager {
public:
	LightsManager();
	~LightsManager() = default;

	void addPointLight(const glm::vec3& position, const glm::vec3& color = glm::vec3(1.0f), float intensity = 5.0f);
	void addDirectionalLight(float angleUp, float angleGround, const glm::vec3& color = glm::vec3(1.0f), float intensity = 1.0f);
	void duplicateSelectedPointLight();
	void duplicateSelectedDirectionalLight();

	void setUniforms(UniformUpdateList& list);

	void ImGui_LightsList();
	void ImGui_SelectedLightSliders();
	void ImGui_AddLightOfSelectedTypeButton();

	Light* selectedLight();
	void trySetSelectedPointLightPosition(const glm::vec3& position);

private:
	LightType m_selectedLightType;
	int m_selectedPointIndex;
	int m_selectedDirectionalIndex;

	Light m_ambiantLight;
	std::vector<PointLight> m_pointLights;
	std::vector<DirectionalLight> m_directionalLights;
};