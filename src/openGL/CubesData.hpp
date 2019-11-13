#pragma once

#include <glad/glad.h>


class CubesData {
public: 
	CubesData() = default;
	CubesData(unsigned int width, unsigned int height, unsigned int depth);
	~CubesData();

	void draw();

private:
	GLuint m_vboID;
	GLuint m_vaoID;
	GLuint m_iboID;
};