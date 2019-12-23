#include "Locate.hpp"

#include "App.hpp"

MaterialsManager& Locate::materialsManager() {
	return App::Get().m_cubesMap.getMaterialsManager();
}

History& Locate::history(HistoryType type) {
	return App::Get().m_histories.getHistory(type);
}

CubesMap& Locate::cubesMap() {
	return App::Get().m_cubesMap;
}

ShaderLibrary& Locate::shaderLibrary() {
	return App::Get().m_shaders;
}

UniformUpdateList& Locate::cameraUniforms() {
	return App::Get().m_cameraUniforms;
}

UniformUpdateList& Locate::lightUniforms() {
	return App::Get().m_lightUniforms;
}