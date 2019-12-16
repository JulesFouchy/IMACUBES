#include "Locate.hpp"

#include "App.hpp"

History& Locate::history(HistoryType type) {
	return App::Get().m_histories.getHistory(type);
}