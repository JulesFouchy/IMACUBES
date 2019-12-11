#pragma once

#include <glad/glad.h>
#include "glm/glm.hpp"
#include "vector"

class CubesGroup {
public:
	static void Initialize();
	static void ShutDown();
	CubesGroup(unsigned int width=0, unsigned int height=0, unsigned int depth=0);
	CubesGroup(const CubesGroup& other);
	~CubesGroup();


	void addCube(glm::vec3 position); 
	void draw();
	void drawWireframe();

private:
	GLuint m_vaoID;
	GLuint  m_cubePositionsVBO_ID;

	static GLuint m_cubeMeshVBO_ID;
	static GLuint m_cubeMeshIBO_ID;
	static GLuint m_cubeWireframeIBO_ID;

	std::vector<glm::vec3> m_positions;
};

