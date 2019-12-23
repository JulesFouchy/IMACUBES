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

	void addCube(glm::ivec3 pos, bool bPushActionInHistory = true); // Dont forget to call history.beginUndoGroup() if you want to push the action in history !
	void removeCube(glm::ivec3 pos, bool bPushActionInHistory = true);

	inline bool cubeExists(glm::ivec3 pos) { return getMaterialLocationOf(pos).isValid(); }

	inline size_t width() { return m_width; }
	inline size_t height() { return m_height; }
	inline size_t depth() { return m_depth; }

	inline bool isPositionInsideWorld(const glm::vec3& pos) { return pos.x > -0.5 && pos.x < m_width - 0.5 && pos.y > -0.5 && pos.y < m_height - 0.5 && pos.z > -0.5 && pos.z < m_depth - 0.5; }

public: //tmp, should be private
	size_t index1Dfrom3D(glm::ivec3 id3D) const;
	bool isIDvalid(glm::ivec3 id3D) const;
	inline const MaterialLocation& getMaterialLocationOf(glm::ivec3 id3D) const { return m_cubesLocations[index1Dfrom3D(id3D)]; }
	void setMaterialLocation(glm::ivec3 id3D, const MaterialLocation& matLoc, bool bPushActionInHistory = true);
	inline MaterialsManager& getMaterialsManager() { return m_materialsManager;	}

private:
	size_t m_width;
	size_t m_height;
	size_t m_depth;
	std::vector<MaterialLocation> m_cubesLocations;
	MaterialsManager m_materialsManager;
};