#pragma once

#include <glad/glad.h>
#include "glm/glm.hpp"
#include "vector"

class CubesGroup_WithoutMaterialIndices {
public:
	static void Initialize();
	static void ShutDown();
	CubesGroup_WithoutMaterialIndices();
	CubesGroup_WithoutMaterialIndices(const CubesGroup_WithoutMaterialIndices& other);
	virtual ~CubesGroup_WithoutMaterialIndices();


	void addCube(glm::vec3 position);
	virtual void removeCube(glm::vec3 position);
	virtual void removeAllCubes();
	void draw();
	void drawWireframe();

protected:
	virtual void createOpenGLStuffs();
	virtual void updateGPU();
	int findCubeAt(glm::vec3 position);

protected:
	bool bMustUpdateGPU;

	GLuint m_vaoID;
	GLuint m_cubesPositionsVBO_ID;
	std::vector<glm::vec3> m_positions;

	static GLuint m_cubeMeshVBO_ID;
	static GLuint m_cubeMeshIBO_ID;
	static GLuint m_cubeWireframeIBO_ID;
};

