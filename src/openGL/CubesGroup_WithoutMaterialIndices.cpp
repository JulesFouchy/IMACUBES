#include "CubesGroup_WithoutMaterialIndices.hpp"

#include "Debugging/gl-exception.h"
#include "Debugging/Log.hpp"

#include "Locator/Locate.hpp"

#include "CubeMaths/CubeMaths.hpp"

#include <algorithm>

GLuint CubesGroup_WithoutMaterialIndices::m_cubeMeshPositionsVBO_ID;
GLuint CubesGroup_WithoutMaterialIndices::m_cubeMeshNormalsVBO_ID;
GLuint CubesGroup_WithoutMaterialIndices::m_cubeMeshTexCoordsVBO_ID;
GLuint CubesGroup_WithoutMaterialIndices::m_cubeMeshFaceIdVBO_ID;
GLuint CubesGroup_WithoutMaterialIndices::m_cubeMeshIBO_ID;
GLuint CubesGroup_WithoutMaterialIndices::m_cubeWireframeIBO_ID;

void CubesGroup_WithoutMaterialIndices::Initialize() {
	float cubeMeshPositions[] = {
		// Front face
		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		// Back face
		-0.5f, -0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		// Top face
		-0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		// Bot face 
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		// Left face 
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		// Right face 
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
	};

	float cubeMeshNormals[] = {
		// Front face
		 0.0f,  0.0f,  1.0f,
		 0.0f,  0.0f,  1.0f,
		 0.0f,  0.0f,  1.0f,
		 0.0f,  0.0f,  1.0f,
		// Back face
		 0.0f,  0.0f, -1.0f,
		 0.0f,  0.0f, -1.0f,
		 0.0f,  0.0f, -1.0f,
		 0.0f,  0.0f, -1.0f,
		// Top face
		 0.0f,  1.0f,  0.0f,
		 0.0f,  1.0f,  0.0f,
		 0.0f,  1.0f,  0.0f,
		 0.0f,  1.0f,  0.0f,
		// Bot face 
		 0.0f, -1.0f,  0.0f,
		 0.0f, -1.0f,  0.0f,
		 0.0f, -1.0f,  0.0f,
		 0.0f, -1.0f,  0.0f,
		// Left face 
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,
		// Right face 
		 1.0f,  0.0f,  0.0f,
		 1.0f,  0.0f,  0.0f,
		 1.0f,  0.0f,  0.0f,
		 1.0f,  0.0f,  0.0f,
	};

	float cubeMeshTexCoords[] = {
		 // Front face
		 0.0f,  0.0f,
		 1.0f,  0.0f,
		 1.0f,  1.0f,
		 0.0f,  1.0f,
		 // Back face
		 0.0f,  0.0f,
		 0.0f,  1.0f,
		 1.0f,  1.0f,
		 1.0f,  0.0f,
		 // Top face
		 0.0f,  0.0f,
		 0.0f,  1.0f,
		 1.0f,  1.0f,
		 1.0f,  0.0f,
		 // Bot face 
		 0.0f,  0.0f,
		 1.0f,  0.0f,
		 1.0f,  1.0f,
		 0.0f,  1.0f,
		 // Left face 
		 0.0f,  0.0f,
		 0.0f,  1.0f,
		 1.0f,  1.0f,
		 1.0f,  0.0f,
		 // Right face 
		 0.0f,  0.0f,
		 1.0f,  0.0f,
		 1.0f,  1.0f,
		 0.0f,  1.0f,
	};

	int cubeMeshFaceIds[] = {
		// Front face
		5, 5, 5, 5,
		// Back face
		4, 4, 4, 4,
		// Top face
		3, 3, 3, 3,
		// Bot face 
		2, 2, 2, 2,
		// Left face 
		0, 0, 0, 0,
		// Right face 
		1, 1, 1, 1,
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
		9, 15,
		10, 14,
		11, 13
	};
	// gen buffers
	GLCall(glGenBuffers(1, &m_cubeMeshPositionsVBO_ID));
	GLCall(glGenBuffers(1, &m_cubeMeshNormalsVBO_ID));
	GLCall(glGenBuffers(1, &m_cubeMeshTexCoordsVBO_ID));
	GLCall(glGenBuffers(1, &m_cubeMeshFaceIdVBO_ID));
	GLCall(glGenBuffers(1, &m_cubeMeshIBO_ID));
	GLCall(glGenBuffers(1, &m_cubeWireframeIBO_ID));
	// VBO data vertices positions
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_cubeMeshPositionsVBO_ID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(cubeMeshPositions), cubeMeshPositions, GL_STATIC_DRAW));
	// VBO data normals
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_cubeMeshNormalsVBO_ID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(cubeMeshNormals), cubeMeshNormals, GL_STATIC_DRAW));
	// VBO data tex coords
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_cubeMeshTexCoordsVBO_ID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(cubeMeshTexCoords), cubeMeshTexCoords, GL_STATIC_DRAW));
	// VBO data face IDs
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_cubeMeshFaceIdVBO_ID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(cubeMeshFaceIds), cubeMeshFaceIds, GL_STATIC_DRAW));
	// IBO data
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_cubeMeshIBO_ID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeMeshIBO), cubeMeshIBO, GL_STATIC_DRAW));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	// IBO data
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_cubeWireframeIBO_ID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeWireframeIBO), cubeWireframeIBO, GL_STATIC_DRAW));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void CubesGroup_WithoutMaterialIndices::ShutDown() {
	GLCall(glDeleteBuffers(1, &m_cubeMeshPositionsVBO_ID));
	GLCall(glDeleteBuffers(1, &m_cubeMeshNormalsVBO_ID));
	GLCall(glDeleteBuffers(1, &m_cubeMeshTexCoordsVBO_ID));
	GLCall(glDeleteBuffers(1, &m_cubeMeshFaceIdVBO_ID));
	GLCall(glDeleteBuffers(1, &m_cubeMeshIBO_ID));
	GLCall(glDeleteBuffers(1, &m_cubeWireframeIBO_ID));
}

CubesGroup_WithoutMaterialIndices::CubesGroup_WithoutMaterialIndices()
	: bMustUpdateGPU(true)
{
	createOpenGLStuffs();
}

CubesGroup_WithoutMaterialIndices::CubesGroup_WithoutMaterialIndices(const CubesGroup_WithoutMaterialIndices& other)
	: m_positions(other.m_positions), bMustUpdateGPU(true)
{
	createOpenGLStuffs();
}

void CubesGroup_WithoutMaterialIndices::createOpenGLStuffs() {
	// Generate buffers and VAO
	GLCall(glGenBuffers(1, &m_cubesPositionsVBO_ID));
	GLCall(glGenVertexArrays(1, &m_vaoID));
	// VBO attrib pointer
	GLCall(glBindVertexArray(m_vaoID));
		// Vertices positions
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_cubeMeshPositionsVBO_ID));
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0));
		// Normals
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_cubeMeshNormalsVBO_ID));
	GLCall(glEnableVertexAttribArray(3));
	GLCall(glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0));
		// Texture coordinates
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_cubeMeshTexCoordsVBO_ID));
	GLCall(glEnableVertexAttribArray(4));
	GLCall(glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));
		// Face IDs
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_cubeMeshFaceIdVBO_ID));
	GLCall(glEnableVertexAttribArray(5));
	GLCall(glVertexAttribIPointer(5, 1, GL_INT, sizeof(int), 0));
		// Cubes positions
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_cubesPositionsVBO_ID));
	GLCall(glEnableVertexAttribArray(1));
	GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0));
	GLCall(glVertexAttribDivisor(1, 1));
		//
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));
}

CubesGroup_WithoutMaterialIndices::~CubesGroup_WithoutMaterialIndices() {
	GLCall(glDeleteBuffers(1, &m_cubesPositionsVBO_ID));
	GLCall(glDeleteVertexArrays(1, &m_vaoID));
}

void CubesGroup_WithoutMaterialIndices::updateGPU() {
	// Positions
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_cubesPositionsVBO_ID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float) * m_positions.size(), m_positions.size() > 0 ? &m_positions[0] : nullptr, GL_STATIC_DRAW));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	//
	bMustUpdateGPU = false;
}


void CubesGroup_WithoutMaterialIndices::addCube(const glm::ivec3& position) {
	removeCube(position);
	addCube_NoExistenceCheck(position);
}


void CubesGroup_WithoutMaterialIndices::addCube_NoExistenceCheck(const glm::ivec3& position) {
	m_positions.push_back(position);
	m_indicesMap[Locate::cubesMap().index1Dfrom3D(position)] = m_positions.size() - 1;
	bMustUpdateGPU = true;
}

int CubesGroup_WithoutMaterialIndices::removeCube(const glm::ivec3& position) {
	int index = findCubeAt(position);
	// if cube exists
	if (index != -1) {
		// remove it from hash map
		m_indicesMap.erase(Locate::cubesMap().index1Dfrom3D(position));
		// remove it from vector of positions
		int lastIndex = m_positions.size() - 1;
		if (lastIndex != index) { // import because otherwise next line recreates the entry that was just removed in hash map
			m_indicesMap[Locate::cubesMap().index1Dfrom3D(CubeMaths::CubeContaining(m_positions.back()))] = index;
			std::swap(m_positions[index], m_positions[lastIndex]);
		}
		m_positions.pop_back();
		// update GPU
		bMustUpdateGPU = true;
	}
	return index;
}

void CubesGroup_WithoutMaterialIndices::removeAllCubes() {
	m_positions.resize(0);
	m_indicesMap.clear();
	bMustUpdateGPU = true;
}

int CubesGroup_WithoutMaterialIndices::findCubeAt(const glm::ivec3& position) {
	auto it = m_indicesMap.find(Locate::cubesMap().index1Dfrom3D(position));
	if (it != m_indicesMap.end())
		return (*it).second;
	return -1;
}

void CubesGroup_WithoutMaterialIndices::draw() {
	if (bMustUpdateGPU)
		updateGPU();
	GLCall(glBindVertexArray(m_vaoID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_cubeMeshIBO_ID));
	GLCall(glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, m_positions.size()));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));
}

void CubesGroup_WithoutMaterialIndices::drawWireframe() {
	if (bMustUpdateGPU)
		updateGPU();
	GLCall(glBindVertexArray(m_vaoID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_cubeWireframeIBO_ID));
	GLCall(glDrawElementsInstanced(GL_LINES, 24, GL_UNSIGNED_INT, 0, m_positions.size()));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));
}
