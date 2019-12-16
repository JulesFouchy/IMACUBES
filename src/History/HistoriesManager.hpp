#pragma once

#include "History.hpp"
#include "HistoryTypes.hpp"

#include <vector>

class HistoriesManager {
public:
	HistoriesManager();
	~HistoriesManager() = default;

	void ImGuiWindow();

	inline History& getActiveHistory() { return m_histories[m_activeHistoryIndex]; }
	inline History& getHistory(HistoryType type) { m_activeHistoryIndex = (int)type;  return m_histories[(int)type]; }

private:
	std::vector<History> m_histories;
	int m_activeHistoryIndex;
};