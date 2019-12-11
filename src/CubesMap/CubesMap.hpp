#pragma once

#include "Material/MaterialLocation.hpp"
#include "Material/MaterialsManager.hpp"

#include <glm/glm.hpp>
#include <vector>

class CubesMap {
friend class Locate;
public:
	CubesMap(size_t width, size_t height, size_t depth);
	~CubesMap() = default;

private:
	size_t index1Dfrom3D(glm::ivec3 id3D);

	inline MaterialsManager& getMaterialsManager() { return m_materialsManager;	}

private:
	size_t m_width;
	size_t m_height;
	size_t m_depth;
	std::vector<MaterialLocation> m_cubesLocations;
	MaterialsManager m_materialsManager;
};