#include "Cursor.hpp"

#include "Locator/Locate.hpp"
#include "CubesMap/CubesMap.hpp"

#include "Debugging/Log.hpp"

#include "UI/Settings.hpp"

#include "CursorPositioner_OnHoveredCube.hpp"
#include "CursorPositioner_AtAFixedDistance.hpp"

Cursor::Cursor()
	: m_bOnHoveredIsSelected(false)
{
	setCursorPositioner<CursorPositioner_OnHoveredCube>();
}

void Cursor::draw() {
	if (!m_bOnHoveredIsSelected || Settings::SHOW_CURSOR_THROUGH_CUBES) {
		glDisable(GL_DEPTH_TEST);
		m_selectedCubes.drawWireframe();
		glEnable(GL_DEPTH_TEST);
	}
	else
		m_selectedCubes.drawWireframe();
}

void Cursor::setPosition(const glm::ivec3& newPos) {
	if (Locate::cubesMap().isID3Dvalid(newPos)) {
		m_position = newPos;
		m_selectedCubes.removeAllCubes();
		m_selectedCubes.addCube_NoExistenceCheck(m_position);
	}
	else
		spdlog::warn("[Cursor::setPosition] trying to position it outside of world's boundaries");
}

void Cursor::setCubeJustBeforePosition(const glm::ivec3& newPos) {
	if (Locate::cubesMap().isID3Dvalid(newPos)) {
		m_cubeJustBeforePosition = newPos;
		//m_selectedCubes.removeAllCubes();
		//m_selectedCubes.addCube_NoExistenceCheck(m_cubeJustBeforePosition);
	}
	else
		spdlog::warn("[Cursor::setCubeJustBeforePosition] trying to position it outside of world's boundaries");
}

void Cursor::translate(const glm::ivec3& dl) {
	setPosition(getPosition() + dl);
	setCubeJustBeforePosition(getCubeJustBeforePosition() + dl);
}

void Cursor::switchCursorPositioner() {
	if (m_bOnHoveredIsSelected)
		setCursorPositioner<CursorPositioner_AtAFixedDistance>();
	else
		setCursorPositioner<CursorPositioner_OnHoveredCube>();
}