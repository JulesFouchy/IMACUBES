#include "LightsManager.hpp"

#include <imgui/imgui.h>

#include "Debugging/Log.hpp"

#include "UI/Settings.hpp"

LightsManager::LightsManager()
	: m_selectedLightType(LightType::Directional), m_selectedPointIndex(0), m_selectedDirectionalIndex(0),
	  m_ambiantLight("Ambiant Light")
{
	addPointLight(glm::vec3(0.0f));
	addDirectionalLight(glm::vec3(-49., -173, 167));
}

void LightsManager::addPointLight(const glm::vec3& position, const glm::vec3& color, float intensity) {
	if (m_pointLights.size() < Settings::MAX_NB_OF_LIGHTS_OF_A_GIVEN_TYPE)
		m_pointLights.emplace_back(position, color, intensity, "PointLight" + std::to_string(m_pointLights.size()));
	else
		spdlog::warn("Sorry you can't have more than {} lights of a given type :/", Settings::MAX_NB_OF_LIGHTS_OF_A_GIVEN_TYPE);
}

void LightsManager::addDirectionalLight(const glm::vec3& direction, const glm::vec3& color, float intensity) {
	if (m_directionalLights.size() < Settings::MAX_NB_OF_LIGHTS_OF_A_GIVEN_TYPE)
		m_directionalLights.emplace_back(direction, color, intensity, "DirectionalLight" + std::to_string(m_directionalLights.size()));
	else
		spdlog::warn("Sorry you can't have more than {} lights of a given type :/", Settings::MAX_NB_OF_LIGHTS_OF_A_GIVEN_TYPE);
}

void LightsManager::duplicateSelectedPointLight() {
	const PointLight& light = m_pointLights[m_selectedPointIndex];
	addPointLight(light.m_position, light.m_color, light.m_intensity);
}

void LightsManager::duplicateSelectedDirectionalLight() {
	const DirectionalLight& light = m_directionalLights[m_selectedDirectionalIndex];
	addDirectionalLight(light.m_direction, light.m_color, light.m_intensity);
}

void LightsManager::setUniforms(UniformUpdateList& list) {
	// Ambiant
	m_ambiantLight.setUniforms("u_ambiant", list);
	// Points
	list.setUniform("u_nbOfPointLights", (int)m_pointLights.size());
	for(int i = 0; i < m_pointLights.size(); ++i)
		m_pointLights[i].setUniforms("u_points["+std::to_string(i)+"]", list);
	// Directionals
	list.setUniform("u_nbOfDirectionalLights", (int)m_directionalLights.size());
	for (int i = 0; i < m_directionalLights.size(); ++i)
		m_directionalLights[i].setUniforms("u_directionals[" + std::to_string(i) + "]", list);
}


void LightsManager::ImGui_LightsList() {
	ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
	if (ImGui::BeginTabBar("LightsTabBar", tab_bar_flags))
	{
		if (ImGui::BeginTabItem("Ambiant"))
		{
			m_selectedLightType = LightType::Ambiant;
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Point"))
		{
			m_selectedLightType = LightType::Point;
			for (int k = 0; k < m_pointLights.size(); ++k) {
				if (ImGui::Selectable(m_pointLights[k].getName().c_str(), m_selectedPointIndex == k ))
					m_selectedPointIndex = k;
			}
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Directional"))
		{
			m_selectedLightType = LightType::Directional;
			for (int k = 0; k < m_directionalLights.size(); ++k) {
				if (ImGui::Selectable(m_directionalLights[k].getName().c_str(), m_selectedDirectionalIndex == k))
					m_selectedDirectionalIndex = k;
			}
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
}

void LightsManager::ImGui_SelectedLightSliders() {
	selectedLight()->ImGui_Sliders();
}

void LightsManager::ImGui_AddLightOfSelectedTypeButton() {
	if (ImGui::Button("Add light")) {
		switch (m_selectedLightType)
		{
		case LightType::Point:
			return duplicateSelectedPointLight();
			break;
		case LightType::Directional:
			return duplicateSelectedDirectionalLight();
			break;
		default:
			break;
		}
	}
}

Light* LightsManager::selectedLight() {
	switch (m_selectedLightType)
	{
	case LightType::Ambiant :
		return &m_ambiantLight;
		break;
	case LightType::Point :
		return &m_pointLights[m_selectedPointIndex];
		break;
	case LightType::Directional:
		return &m_directionalLights[m_selectedDirectionalIndex];
		break;
	default:
		return nullptr;
		break;
	}
}