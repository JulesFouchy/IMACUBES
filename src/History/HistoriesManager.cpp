#include "HistoriesManager.hpp"

HistoriesManager::HistoriesManager()
	: m_activeHistoryIndex(0)
{
	m_histories.emplace_back("Uniforms");
	m_histories.emplace_back("Cubes");
}