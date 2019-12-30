#include "HistoriesManager.hpp"

#include <imgui/imgui.h>

HistoriesManager::HistoriesManager()
	: m_activeHistoryIndex(0)
{
	m_histories.emplace_back("Materials");
	m_histories.emplace_back("Cubes");
	m_histories.emplace_back("Lights");
}

void HistoriesManager::_ImGui_ActiveHistory() {
	int k = 0;
	for (History& history : m_histories) {
		if (ImGui::Selectable(history.getName().c_str(), k == m_activeHistoryIndex)) {
			m_activeHistoryIndex = k;
		}
		k++;
	}
}