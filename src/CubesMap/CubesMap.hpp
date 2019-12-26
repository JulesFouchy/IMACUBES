#pragma once

#include "Material/MaterialLocation.hpp"
#include "Material/MaterialsManager.hpp"

#include <glm/glm.hpp>
#include <vector>

class CubesMap {
friend class Locate;
public:
	CubesMap(int width, int height, int depth);
	~CubesMap() = default;

	void addCube(glm::ivec3 pos, bool bPushActionInHistory = true); // Dont forget to call history.beginUndoGroup() if you want to push the action in history !
	void removeCube(glm::ivec3 pos, bool bPushActionInHistory = true);

	inline bool cubeExists(glm::ivec3 pos) { return getMaterialLocationOf(pos).isValid(); }

	inline int width() { return m_width; }
	inline int height() { return m_height; }
	inline int depth() { return m_depth; }

	bool isPositionInsideWorld(const glm::vec3& pos);

public: //TODO should be private
	int minX() const;
	int maxX() const;
	int minY() const;
	int maxY() const;
	int minZ() const;
	int maxZ() const;
	int index1Dfrom3D(glm::ivec3 id3D) const;
	bool isID3Dvalid(glm::ivec3 id3D) const;
	inline const MaterialLocation& getMaterialLocationOf(glm::ivec3 id3D) const { return m_cubesLocations[index1Dfrom3D(id3D)]; }
	void setMaterialLocation(glm::ivec3 id3D, const MaterialLocation& matLoc, bool bPushActionInHistory = true);
	inline MaterialsManager& getMaterialsManager() { return m_materialsManager;	}

private:
	int m_width;
	int m_height;
	int m_depth;
	std::vector<MaterialLocation> m_cubesLocations;
	MaterialsManager m_materialsManager;
};