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

	void addCube(glm::ivec3 pos);
	void removeCube(glm::ivec3 pos);

private:
	size_t index1Dfrom3D(glm::ivec3 id3D) const;
	bool isIDvalid(glm::ivec3 id3D) const;
	inline const MaterialLocation& getMaterialLocationOf(glm::ivec3 id3D) const { return m_cubesLocations[index1Dfrom3D(id3D)]; }
	inline void setMaterialLocation(glm::ivec3 id3D, const MaterialLocation& matLoc) { m_cubesLocations[index1Dfrom3D(id3D)] = matLoc; }
	inline MaterialsManager& getMaterialsManager() { return m_materialsManager;	}

private:
	size_t m_width;
	size_t m_height;
	size_t m_depth;
	std::vector<MaterialLocation> m_cubesLocations;
	MaterialsManager m_materialsManager;
};