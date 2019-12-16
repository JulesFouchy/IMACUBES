#include "HistoriesManager.hpp"

#include <imgui/imgui.h>

HistoriesManager::HistoriesManager()
	: m_activeHistoryIndex(0)
{
	m_histories.emplace_back("Uniforms");
	m_histories.emplace_back("Cubes");
}

void HistoriesManager::ImGuiWindow() {
	ImGui::Begin("Histories");
	int k = 0;
	for (History& history : m_histories) {
		if (ImGui::Selectable(history.getName().c_str(), k == m_activeHistoryIndex)) {
			m_activeHistoryIndex = k;
		}
		k++;
	}
	ImGui::End();
}