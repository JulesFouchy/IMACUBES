#include "Cursor.hpp"

#include "Locator/Locate.hpp"

Cursor::Cursor(int x, int y, int z) {
	setPosition(glm::ivec3(x, y, z));
}

void Cursor::draw() {
	glDisable(GL_DEPTH_TEST);
	m_selectedCubes.drawWireframe();
	glEnable(GL_DEPTH_TEST);
}

void Cursor::setPosition(const glm::ivec3& newPos) {
	if (Locate::cubesMap().isPositionInsideWorld(newPos)) {
		m_position = newPos;
		m_selectedCubes.removeAllCubes();
		m_selectedCubes.addCube_NoExistenceCheck(m_position);
	}
	else
		spdlog::warn("[Cursor::setPosition] trying to position it outside of world's boundaries");
}