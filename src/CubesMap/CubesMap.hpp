#pragma once

#include "Material/MaterialLocation.hpp"

#include <glm/glm.hpp>
#include <vector>

class CubesMap {
public:
	CubesMap(size_t width, size_t height, size_t depth);
	~CubesMap() = default;

private:
	size_t index1Dfrom3D(glm::ivec3 id3D);

private:
	size_t m_width;
	size_t m_height;
	size_t m_depth;
	std::vector<MaterialLocation> m_cubesLocations;
};