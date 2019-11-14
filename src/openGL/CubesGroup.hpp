#pragma once

#include <glad/glad.h>


class CubesGroup {
public:
	static void Initialize();
	static void ShutDown();
	CubesGroup(unsigned int width, unsigned int height, unsigned int depth);
	~CubesGroup();

	void draw();
	void drawWireframe();

private:
	GLuint m_vaoID;

	static GLuint m_cubeMeshVBO_ID;
	static GLuint m_cubeMeshIBO_ID;
	static GLuint m_cubeWireframeIBO_ID;
};