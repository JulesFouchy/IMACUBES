#pragma once

#include <glad/glad.h>
#include "glm/glm.hpp"
#include <vector>
#include <unordered_map>

class CubesGroup_WithoutMaterialIndices {
public:
	static void Initialize();
	static void ShutDown();
	CubesGroup_WithoutMaterialIndices();
	CubesGroup_WithoutMaterialIndices(const CubesGroup_WithoutMaterialIndices& other);
	virtual ~CubesGroup_WithoutMaterialIndices();


	void addCube(const glm::ivec3& position);
	void addCube_NoExistenceCheck(const glm::ivec3& position);
	virtual int removeCube(const glm::ivec3& position);
	virtual void removeAllCubes();
	void draw();
	void drawWireframe();

protected:
	virtual void createOpenGLStuffs();
	virtual void updateGPU();
	int findCubeAt(const glm::ivec3& position);

protected:
	bool bMustUpdateGPU;

	GLuint m_vaoID;
	GLuint m_cubesPositionsVBO_ID;
	std::vector<glm::vec3> m_positions;
	std::unordered_map<int, int> m_indicesMap;

	static GLuint m_cubeMeshPositionsVBO_ID;
	static GLuint m_cubeMeshNormalsVBO_ID;
	static GLuint m_cubeMeshTexCoordsVBO_ID;
	static GLuint m_cubeMeshIBO_ID;
	static GLuint m_cubeWireframeIBO_ID;
};

