#pragma once

#include <glad/glad.h>


class CubesGroup {
public:
	static void Initialize();
	static void ShutDown();
	CubesGroup(unsigned int width=0, unsigned int height=0, unsigned int depth=0);
	~CubesGroup();

	void draw();
	void drawWireframe();

private:
	GLuint m_vaoID;

	static GLuint m_cubeMeshVBO_ID;
	static GLuint m_cubeMeshIBO_ID;
	static GLuint m_cubeWireframeIBO_ID;
};