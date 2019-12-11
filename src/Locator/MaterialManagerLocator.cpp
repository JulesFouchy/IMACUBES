#include "MaterialManagerLocator.hpp"

#include "App.hpp"

MaterialsManager& Locate::materialsManager() {
	return App::Get().m_cubesMap.getMaterialsManager();
}