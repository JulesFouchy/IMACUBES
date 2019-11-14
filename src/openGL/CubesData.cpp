#include "CubesData.hpp"

#include "OpenGL/gl-exception.h"


CubesData::CubesData(unsigned int width, unsigned int height, unsigned int depth){
	const int nbFaces = 6;
	const int vboSize = 4 * 3 * nbFaces;
	const int iboSize = 6 * nbFaces;
	const float cubeVBO[vboSize] = {
		// position
		// Back face
		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		// Back face
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		// Top face
		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		// Bottom face 
		-0.5f,  -0.5f, -0.5f,
		 0.5f,  -0.5f, -0.5f,
		 0.5f,  -0.5f,  0.5f,
		-0.5f,  -0.5f,  0.5f,
		// Left face 
		-0.5f,  -0.5f, -0.5f,
		-0.5f,   0.5f, -0.5f,
		-0.5f,   0.5f,  0.5f,
		-0.5f,  -0.5f,  0.5f,
		// Right face 
		 0.5f,  -0.5f, -0.5f,
		 0.5f,   0.5f, -0.5f,
		 0.5f,   0.5f,  0.5f,
		 0.5f,  -0.5f,  0.5f,
	};

	const unsigned int cubeIBO[iboSize] = {
		// Back face
		0, 1, 2,
		0, 2, 3,
		// Front face
		4, 5, 6,
		4, 6, 7,
		// Top face
		8, 9, 10,
		8, 10, 11,
		// Bottom face
		12, 13 , 14,
		12, 14, 15,
		// Left face
		16, 17 , 18,
		16, 18, 19,
		// Right face
		20, 21 , 22,
		20, 22, 23,
	};

	unsigned int cubeWireframeIBO[] = {
		// Top face
		8, 9,
		9, 10,
		10, 11,
		11, 8,
		// Bot face
		12, 13,
		13, 14,
		14, 15, 
		15, 12,
		// Laterals
		8, 12,
		9, 13,
		10, 14,
		11, 15
	};

	// gen buffers
	GLCall(glGenBuffers(1, &m_vboID));
	GLCall(glGenVertexArrays(1, &m_vaoID));
	GLCall(glGenBuffers(1, &m_iboID));
	GLCall(glGenBuffers(1, &m_iboWireframeID));
	// VBO data
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vboID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, vboSize * sizeof(float), cubeVBO, GL_STATIC_DRAW));
	// VBO attrib pointer
	GLCall(glBindVertexArray(m_vaoID));
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));
	// IBO data
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, iboSize * sizeof(unsigned int), cubeIBO, GL_STATIC_DRAW));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	// IBO data
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboWireframeID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeWireframeIBO), cubeWireframeIBO, GL_STATIC_DRAW));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

CubesData::~CubesData(){
	GLCall(glDeleteBuffers(1, &m_vboID));
	GLCall(glDeleteBuffers(1, &m_iboID));
	GLCall(glDeleteBuffers(1, &m_iboWireframeID));
	GLCall(glDeleteVertexArrays(1, &m_vaoID));
}


void CubesData::draw() {
	GLCall(glBindVertexArray(m_vaoID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboID));

	GLCall(glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, 3));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void CubesData::drawWireframe() {
	GLCall(glBindVertexArray(m_vaoID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboWireframeID));

	GLCall(glDrawElementsInstanced(GL_LINES, 24, GL_UNSIGNED_INT, 0, 3));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
