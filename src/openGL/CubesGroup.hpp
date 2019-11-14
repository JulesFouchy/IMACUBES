#pragma once

#include <glad/glad.h>


class CubesGroup {
public:
	CubesGroup(unsigned int width, unsigned int height, unsigned int depth);
	~CubesGroup();

	void draw();
	void drawWireframe();

private:
	GLuint m_cubeMeshVBO_ID;
	GLuint m_vaoID;
	GLuint m_cubeMeshIBO_ID;
	GLuint m_cubeWireframeIBO_ID;
};