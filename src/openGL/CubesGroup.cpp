#include "CubesGroup.hpp"

#include "Debugging/gl-exception.h"

#include "Debugging/Log.hpp"

#include <algorithm>

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

CubesGroup::CubesGroup(const CubesGroup& other)
	: m_positions(other.m_positions), m_materialIndices(other.m_materialIndices)
{
	createOpenGLStuffs();
}

void CubesGroup::createOpenGLStuffs(){
	// Generate buffers and VAO
	GLCall(glGenBuffers(1, &m_cubesPositionsVBO_ID));
	GLCall(glGenBuffers(1, &m_cubesMaterialIndicesVBO_ID));
	GLCall(glGenVertexArrays(1, &m_vaoID));
	// VBO attrib pointer
	GLCall(glBindVertexArray(m_vaoID));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_cubeMeshVBO_ID));
			GLCall(glEnableVertexAttribArray(0));
			GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_cubesPositionsVBO_ID));
			GLCall(glEnableVertexAttribArray(1));
			GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0));
			GLCall(glVertexAttribDivisor(1, 1));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_cubesMaterialIndicesVBO_ID));
			GLCall(glEnableVertexAttribArray(2));
			GLCall(glVertexAttribIPointer(2, 1, GL_INT, sizeof(int), 0));
			GLCall(glVertexAttribDivisor(2, 1));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));
}

CubesGroup::~CubesGroup(){
	GLCall(glDeleteBuffers(1, &m_cubesPositionsVBO_ID));
	GLCall(glDeleteBuffers(1, &m_cubesMaterialIndicesVBO_ID));
	GLCall(glDeleteVertexArrays(1, &m_vaoID));
}

void CubesGroup::updateGPU() {
	// Positions
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_cubesPositionsVBO_ID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float) * m_positions.size(), m_positions.size() > 0 ? &m_positions[0] : nullptr, GL_STATIC_DRAW));
	// Material indices
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_cubesMaterialIndicesVBO_ID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(int) * m_materialIndices.size(), m_materialIndices.size() > 0 ? &m_materialIndices[0] : nullptr, GL_STATIC_DRAW));
	//
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}


void CubesGroup::addCube(int materialID, glm::vec3 position) {
	assert(materialID > -1);
	m_positions.push_back(position);
	m_materialIndices.push_back(materialID);
	updateGPU();
}

void CubesGroup::removeCube(glm::vec3 position) {
	int index = findCubeAt(position);
	int lastIndex = m_positions.size() - 1;
	std::swap(m_positions[index], m_positions[lastIndex]);
	std::swap(m_materialIndices[index], m_materialIndices[lastIndex]);
	m_positions.pop_back();
	m_materialIndices.pop_back();
	updateGPU();
}

int CubesGroup::findCubeAt(glm::vec3 position) {
	for (int k = 0; k < m_positions.size(); ++k) {
		if (glm::length(position - m_positions[k]) < 0.1f)
			return k;
	}
	return -1;
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
