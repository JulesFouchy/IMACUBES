#pragma once

struct MaterialLocation {
	int shaderID;
	int materialID;

	MaterialLocation(int shaderID, int materialID)
		: shaderID(shaderID), materialID(materialID) {}
};