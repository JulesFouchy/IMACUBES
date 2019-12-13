#include "Locate.hpp"

#include "App.hpp"

History& Locate::history() {
	return App::Get().m_history;
}