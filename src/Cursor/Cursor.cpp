#include "Cursor.hpp"

Cursor::Cursor(int x, int y, int z) {
	setPosition(glm::ivec3(x, y, z));
}

void Cursor::draw() {
	glDisable(GL_DEPTH_TEST);
	m_selectedCubes.drawWireframe();
	glEnable(GL_DEPTH_TEST);
}

void Cursor::setPosition(const glm::ivec3& newPos) {
	m_position = newPos;
	m_selectedCubes.removeAllCubes();
	m_selectedCubes.addCube(0, m_position);
}