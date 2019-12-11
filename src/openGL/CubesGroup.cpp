#include "CubesGroup.hpp"

#include "Debugging/gl-exception.h"

#include "Debugging/Log.hpp"

GLuint CubesGroup::m_cubeMeshVBO_ID;
GLuint CubesGroup::m_cubeMeshIBO_ID;
GLuint CubesGroup::m_cubeWireframeIBO_ID;

void CubesGroup::Initialize() {
	float cubeMeshVBO[] = {
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

	unsigned int cubeMeshIBO[] = {
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
	GLCall(glGenBuffers(1, &m_cubeMeshVBO_ID));
	GLCall(glGenBuffers(1, &m_cubeMeshIBO_ID));
	GLCall(glGenBuffers(1, &m_cubeWireframeIBO_ID));
	// VBO data sommet Cube 
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_cubeMeshVBO_ID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(cubeMeshVBO), cubeMeshVBO, GL_STATIC_DRAW));
	// IBO data
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_cubeMeshIBO_ID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeMeshIBO), cubeMeshIBO, GL_STATIC_DRAW));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	// IBO data
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_cubeWireframeIBO_ID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeWireframeIBO), cubeWireframeIBO, GL_STATIC_DRAW));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void CubesGroup::ShutDown() {
	GLCall(glDeleteBuffers(1, &m_cubeMeshVBO_ID));
	GLCall(glDeleteBuffers(1, &m_cubeMeshIBO_ID));
	GLCall(glDeleteBuffers(1, &m_cubeWireframeIBO_ID));
}

CubesGroup::CubesGroup(){
	createOpenGLStuffs();
}

CubesGroup::CubesGroup(const CubesGroup& other) {
	createOpenGLStuffs();
}

void CubesGroup::createOpenGLStuffs(){
	// Generate VAO
	GLCall(glGenVertexArrays(1, &m_vaoID));
	GLCall(glGenBuffers(1, &m_cubePositionsVBO_ID));
	// VBO attrib pointer
	GLCall(glBindVertexArray(m_vaoID));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_cubeMeshVBO_ID));
			GLCall(glEnableVertexAttribArray(0));
			GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_cubePositionsVBO_ID));
			GLCall(glEnableVertexAttribArray(1));
			GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0));
			GLCall(glVertexAttribDivisor(1, 1));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));
}

CubesGroup::~CubesGroup(){
	GLCall(glDeleteVertexArrays(1, &m_vaoID));
	GLCall(glDeleteBuffers(1, &m_cubePositionsVBO_ID));
}


void CubesGroup::addCube(glm::vec3 position) {
	m_positions.push_back(position); 
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_cubePositionsVBO_ID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float) * m_positions.size(), &m_positions[0], GL_STATIC_DRAW));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void CubesGroup::draw() {
	GLCall(glBindVertexArray(m_vaoID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_cubeMeshIBO_ID));
		GLCall(glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, m_positions.size()));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));
}

void CubesGroup::drawWireframe() {
	GLCall(glBindVertexArray(m_vaoID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_cubeWireframeIBO_ID));
		GLCall(glDrawElementsInstanced(GL_LINES, 24, GL_UNSIGNED_INT, 0, m_positions.size()));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));
}
