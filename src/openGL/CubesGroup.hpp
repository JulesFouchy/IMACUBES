#pragma once

#include <glad/glad.h>
#include "glm/glm.hpp"
#include "vector"

class CubesGroup {
public:
	static void Initialize();
	static void ShutDown();
	CubesGroup();
	CubesGroup(const CubesGroup& other);
	~CubesGroup();


	void addCube(int materialID, glm::vec3 position); 
	void removeCube(glm::vec3 position);
	void draw();
	void drawWireframe();

private:
	void createOpenGLStuffs();
	void updateGPU();
	int findCubeAt(glm::vec3 position);

private:
	GLuint m_vaoID;
	GLuint m_cubesPositionsVBO_ID;
	GLuint m_cubesMaterialIndicesVBO_ID;
	std::vector<glm::vec3> m_positions;
	std::vector<int> m_materialIndices;

	static GLuint m_cubeMeshVBO_ID;
	static GLuint m_cubeMeshIBO_ID;
	static GLuint m_cubeWireframeIBO_ID;
};

