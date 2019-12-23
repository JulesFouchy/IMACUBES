#pragma once

#include "Material/MaterialsManager.hpp"
#include "History/History.hpp"
#include "History/HistoryTypes.hpp"
#include "CubesMap/CubesMap.hpp"

class Locate {
public:
	static MaterialsManager& materialsManager();
	static History& history(HistoryType type);
	static CubesMap& cubesMap();
};