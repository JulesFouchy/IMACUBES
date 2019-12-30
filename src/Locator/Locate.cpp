#include "Locate.hpp"

#include "App.hpp"

#include "Material/MaterialsManager.hpp"
#include "History/History.hpp"
#include "History/HistoryTypes.hpp"
#include "CubesMap/CubesMap.hpp"
#include "OpenGL/ShaderLibrary.hpp"
#include "OpenGL/Uniform/UniformUpdateList.hpp"

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