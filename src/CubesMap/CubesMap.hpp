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

	void addCube(const glm::ivec3& pos, bool bPushActionInHistory = true); // Dont forget to call history.beginUndoGroup() if you want to push the action in history !
	void removeCube(const glm::ivec3& pos, bool bPushActionInHistory = true);

	inline bool cubeExists(const glm::ivec3& pos) const { return getMaterialLocationOf(pos).isValid(); }

	inline int width() const { return m_width; }
	inline int height() const { return m_height; }
	inline int depth() const { return m_depth; }
	inline int minValidX() const { return -m_width/2; }
	inline int maxValidX() const { return m_width - m_width/2 - 1; }
	inline int minValidY() const { return -m_height/2; }
	inline int maxValidY() const { return m_height - m_height/2 - 1; }
	inline int minValidZ() const { return -m_depth/2; }
	inline int maxValidZ() const { return m_depth - m_depth/2 - 1; }

	int index1Dfrom3D(const glm::ivec3& id3D) const;
	bool isID3Dvalid(const glm::ivec3& id3D) const;
	bool isPositionInsideWorld(const glm::vec3& pos) const;

private:
	inline const MaterialLocation& getMaterialLocationOf(glm::ivec3 id3D) const { return m_cubesLocations[index1Dfrom3D(id3D)]; }
	void setMaterialLocation(glm::ivec3 id3D, const MaterialLocation& matLoc, bool bPushActionInHistory = true);
	inline MaterialsManager& getMaterialsManager() { return m_materialsManager; }

private:
	int m_width;
	int m_height;
	int m_depth;
	std::vector<MaterialLocation> m_cubesLocations;
	MaterialsManager m_materialsManager;
};