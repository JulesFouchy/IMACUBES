#pragma once

#include "CubesGroup_WithoutMaterialIndices.hpp"

class CubesGroup : public CubesGroup_WithoutMaterialIndices {
public:
	CubesGroup();
	CubesGroup(const CubesGroup& other);
	~CubesGroup();

	void addCube(int materialID, glm::vec3 position) override;
	void removeCube(glm::vec3 position) override;
	void removeAllCubes() override;

	int getCubeMaterialID(const glm::vec3& position);

private:
	void createOpenGLStuffs() override;
	void createOpenGLStuffsRelativeToMaterialIndices();
	void updateGPU() override;

private:
	GLuint m_cubesMaterialIndicesVBO_ID;
	std::vector<int> m_materialIndices;
};