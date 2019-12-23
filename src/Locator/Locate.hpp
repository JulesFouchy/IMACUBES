#pragma once

#include "Material/MaterialsManager.hpp"
#include "History/History.hpp"
#include "History/HistoryTypes.hpp"
#include "CubesMap/CubesMap.hpp"
#include "OpenGL/ShaderLibrary.hpp"
#include "OpenGL/UniformUpdateList.hpp"

class Locate {
public:
	static MaterialsManager& materialsManager();
	static History& history(HistoryType type);
	static CubesMap& cubesMap();
	static ShaderLibrary& shaderLibrary();
	static UniformUpdateList& cameraUniforms();
	static UniformUpdateList& lightUniforms();
};