#pragma once

#include "CubesGroup_WithoutMaterialIndices.hpp"

class CubesGroup : public CubesGroup_WithoutMaterialIndices {
public:
	CubesGroup();
	CubesGroup(const CubesGroup& other);
	CubesGroup(CubesGroup&& other) noexcept;
	~CubesGroup();

	void addCube(int materialID, const glm::ivec3& position);
	int removeCube(const glm::ivec3& position) override;
	void removeAllCubes() override;

	int getCubeMaterialID(const glm::ivec3& position);

private:
	void createOpenGLStuffs() override;
	void createOpenGLStuffsRelativeToMaterialIndices();
	void updateGPU() override;

private:
	GLuint m_cubesMaterialIndicesVBO_ID;
	std::vector<int> m_materialIndices;
};