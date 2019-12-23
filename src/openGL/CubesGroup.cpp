#include "CubesGroup.hpp"

#include "Debugging/gl-exception.h"
#include "Debugging/Log.hpp"

CubesGroup::CubesGroup()
{
	createOpenGLStuffs();
	bMustUpdateGPU = true;
}

CubesGroup::CubesGroup(const CubesGroup& other)
	: CubesGroup_WithoutMaterialIndices(other), m_materialIndices(other.m_materialIndices)
{
	createOpenGLStuffsRelativeToMaterialIndices();
}

void CubesGroup::createOpenGLStuffs() {
	CubesGroup_WithoutMaterialIndices::createOpenGLStuffs();
	createOpenGLStuffsRelativeToMaterialIndices();
}

void CubesGroup::createOpenGLStuffsRelativeToMaterialIndices() {
	// Gen buffer
	GLCall(glGenBuffers(1, &m_cubesMaterialIndicesVBO_ID));
	// VBO attrib pointer
	GLCall(glBindVertexArray(m_vaoID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_cubesMaterialIndicesVBO_ID));
		GLCall(glEnableVertexAttribArray(2));
		GLCall(glVertexAttribIPointer(2, 1, GL_INT, sizeof(int), 0));
		GLCall(glVertexAttribDivisor(2, 1));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));
}

CubesGroup::~CubesGroup() {
	GLCall(glDeleteBuffers(1, &m_cubesMaterialIndicesVBO_ID));
}

void CubesGroup::updateGPU() {
	// Positions
	CubesGroup_WithoutMaterialIndices::updateGPU();
	// Material indices
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_cubesMaterialIndicesVBO_ID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(int) * m_materialIndices.size(), m_materialIndices.size() > 0 ? &m_materialIndices[0] : nullptr, GL_STATIC_DRAW));
	//
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void CubesGroup::addCube(int materialID, const glm::ivec3& position) {
	assert(materialID > -1);
	CubesGroup_WithoutMaterialIndices::addCube(position);
	m_materialIndices.push_back(materialID);
}

int CubesGroup::removeCube(const glm::ivec3& position) {
	int index = CubesGroup_WithoutMaterialIndices::removeCube(position);
	if (index != -1) {
		int lastIndex = m_materialIndices.size() - 1;
		std::swap(m_materialIndices[index], m_materialIndices[lastIndex]);
		m_materialIndices.pop_back();
	}
	return index;
}

void CubesGroup::removeAllCubes() {
	CubesGroup_WithoutMaterialIndices::removeAllCubes();
	m_materialIndices.resize(0);
}

int CubesGroup::getCubeMaterialID(const glm::ivec3& position) {
	int index = findCubeAt(position);
	return m_materialIndices[index];
}