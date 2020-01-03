#include "LightsManager.hpp"

#include <imgui/imgui.h>

#include "Debugging/Log.hpp"

#include "UI/Settings.hpp"

LightsManager::LightsManager()
	: m_selectedLightType(LightType::Directional), m_selectedPointIndex(0), m_selectedDirectionalIndex(0),
	  m_ambiantLight("Ambiant Light")
{
	addPointLight(glm::vec3(0.0f), glm::vec3(1.0f), 0.0f);
	addDirectionalLight(3.441, -1.22, glm::vec3(1.0), 0.45);
}

void LightsManager::addPointLight(const glm::vec3& position, const glm::vec3& color, float intensity) {
	if (m_pointLights.size() < Settings::MAX_NB_OF_LIGHTS_OF_A_GIVEN_TYPE) {
		m_pointLights.emplace_back(position, color, intensity, "PointLight" + std::to_string(m_pointLights.size()));
		m_selectedPointIndex = m_pointLights.size() - 1;
	}
	else
		spdlog::warn("Sorry you can't have more than {} lights of a given type :/", Settings::MAX_NB_OF_LIGHTS_OF_A_GIVEN_TYPE);
}

void LightsManager::addDirectionalLight(float angleUp, float angleGround, const glm::vec3& color, float intensity) {
	if (m_directionalLights.size() < Settings::MAX_NB_OF_LIGHTS_OF_A_GIVEN_TYPE) {
		m_directionalLights.emplace_back(angleUp, angleGround, color, intensity, "DirectionalLight" + std::to_string(m_directionalLights.size()));
		m_selectedDirectionalIndex = m_directionalLights.size() - 1;
	}
	else
		spdlog::warn("Sorry you can't have more than {} lights of a given type :/", Settings::MAX_NB_OF_LIGHTS_OF_A_GIVEN_TYPE);
}

void LightsManager::duplicateSelectedPointLight() {
	const PointLight& light = m_pointLights[m_selectedPointIndex];
	addPointLight(light.m_position.getValue(), light.m_color.getValue(), light.m_intensity.getValue());
}

void LightsManager::duplicateSelectedDirectionalLight() {
	const DirectionalLight& light = m_directionalLights[m_selectedDirectionalIndex];
	addDirectionalLight(light.m_direction.getValue().getAngleGround(), light.m_direction.getValue().getAngleUp(), light.m_color.getValue(), light.m_intensity.getValue());
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
				ImGui::PushID(k);
				if (ImGui::Selectable(m_pointLights[k].getName().c_str(), m_selectedPointIndex == k ))
					m_selectedPointIndex = k;
				ImGui::PopID();
			}
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Directional"))
		{
			m_selectedLightType = LightType::Directional;
			for (int k = 0; k < m_directionalLights.size(); ++k) {
				ImGui::PushID(-k-1);
				if (ImGui::Selectable(m_directionalLights[k].getName().c_str(), m_selectedDirectionalIndex == k))
					m_selectedDirectionalIndex = k;
				ImGui::PopID();
			}
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
}

void LightsManager::ImGui_SelectedLightSliders() {
	selectedLight()->ImGui_Sliders();
}

void LightsManager::ImGui_AddLightOfSelectedTypeButton(bool forcedPress) {
	if (ImGui::Button("Add light") || forcedPress) {
		switch (m_selectedLightType)
		{
		case LightType::Point:
			duplicateSelectedPointLight();
			break;
		case LightType::Directional:
			duplicateSelectedDirectionalLight();
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

void LightsManager::trySetSelectedPointLightPosition(const glm::vec3& position) {
	if (m_selectedLightType == LightType::Point)
		m_pointLights[m_selectedPointIndex].setPosition(position);
}