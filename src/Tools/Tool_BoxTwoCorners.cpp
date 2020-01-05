#include "Tool_BoxTwoCorners.hpp"

#include "CubesMap/BoundingBox.hpp"

#include "Debugging/Log.hpp"

Tool_BoxTwoCorners::Tool_BoxTwoCorners()
	: m_bFirstCornerSelected(false)
{}

void Tool_BoxTwoCorners::update(const Cursor& cursor) {
	if (m_bFirstCornerSelected) {
		m_corner2 = cursor.getCubeJustBeforePosition();
		computePreview();
	}
}

void Tool_BoxTwoCorners::onLeftClicDown(const Cursor& cursor) {
	if (!m_bFirstCornerSelected) {
		m_corner1 = cursor.getCubeJustBeforePosition();
		m_bFirstCornerSelected = true;
	}
	else {
		addCubes();
		m_bFirstCornerSelected = false;
		m_previewGroup.removeAllCubes();
	}
}

void Tool_BoxTwoCorners::onRightClicDown(const Cursor& cursor) {
	if (m_bFirstCornerSelected) {
		removeCubes();
		m_bFirstCornerSelected = false;
		m_previewGroup.removeAllCubes();
	}
}

void Tool_BoxTwoCorners::applyOnShape(std::function<void(const glm::ivec3 & pos)> whatToDoWithPos) {
	BoundingBox bbox(m_corner1, m_corner2);
	for (const glm::ivec3& pos : bbox)
		whatToDoWithPos(pos);
}