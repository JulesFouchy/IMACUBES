#include "Locate.hpp"
#include "App.hpp"

CubesMap& Locate::cubesMap() {
	return App::Get().m_cubesMap;
}