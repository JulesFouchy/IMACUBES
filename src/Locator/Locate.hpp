#pragma once

#include "Material/MaterialsManager.hpp"
#include "History/History.hpp"

class Locate {
public:
	static MaterialsManager& materialsManager();
	static History& history();
};