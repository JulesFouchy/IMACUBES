#include "Locate.hpp"

#include "App.hpp"

#include "Material/MaterialsManager.hpp"
#include "History/History.hpp"
#include "History/HistoryTypes.hpp"
#include "CubesMap/CubesMap.hpp"
#include "OpenGL/ShaderLibrary.hpp"
#include "OpenGL/Uniform/UniformUpdateList.hpp"
#include "Renderer/Renderer.hpp"
#include "Light/LightsManager.hpp"

MaterialsManager& Locate::materialsManager() {
	return App::Get().m_cubesMap.materialsManager();
}

History& Locate::history(HistoryType type) {
	return App::Get().m_histories.getHistory(type);
}

CubesMap& Locate::cubesMap() {
	return App::Get().m_cubesMap;
}

ShaderLibrary& Locate::shaderLibrary() {
	return App::Get().m_shaderLibrary;
}

Renderer& Locate::renderer() {
	return App::Get().m_renderer;
}

LightsManager& Locate::lightsManager() {
	return App::Get().m_lightsManager;
}