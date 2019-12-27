#include "LightsManager.hpp"

#include <imgui/imgui.h>

#include "Debugging/Log.hpp"

LightsManager::LightsManager()
	: m_selectedLightType(LightType::Directional), m_selectedPointIndex(0), m_selectedDirectionalIndex(0),
	  m_ambiantLight("Ambiant Light")
{
	addPointLight(glm::vec3(0.0f));
	addDirectionalLight(glm::vec3(-49., -173, 167));
}

void LightsManager::addPointLight(const glm::vec3& position, const glm::vec3& color, float intensity) {
	m_pointLights.emplace_back(position, color, intensity, "PointLight" + std::to_string(m_pointLights.size()));
}

void LightsManager::addDirectionalLight(const glm::vec3& direction, const glm::vec3& color, float intensity) {
	m_directionalLights.emplace_back(direction, color, intensity, "DirectionalLight" + std::to_string(m_directionalLights.size()));
}

void LightsManager::duplicatePointLight() {
	m_pointLights.push_back(m_pointLights[m_selectedPointIndex]);
	m_pointLights.back().setName("PointLight" + std::to_string(m_pointLights.size() - 1));
}

void LightsManager::duplicateDirectionalLight() {
	m_directionalLights.push_back(m_directionalLights[m_selectedDirectionalIndex]);
	m_directionalLights.back().setName("DirectionalLight" + std::to_string(m_directionalLights.size() - 1));
}

void LightsManager::setUniforms(UniformUpdateList& list) {
	// TODO send all the lights in the vector
	m_ambiantLight.setUniforms("u_ambiant", list);
	m_pointLights[0].setUniforms("u_point", list);
	m_directionalLights[0].setUniforms("u_directional", list);
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
			return duplicatePointLight();
			break;
		case LightType::Directional:
			return duplicateDirectionalLight();
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