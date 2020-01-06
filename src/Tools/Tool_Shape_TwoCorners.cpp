#include "Tool_Shape_TwoCorners.hpp"

Tool_Shape_TwoCorners::Tool_Shape_TwoCorners()
	: m_bFirstCornerSelected(false)
{}

void Tool_Shape_TwoCorners::update(const Cursor& cursor) {
	if (m_bFirstCornerSelected) {
		m_corner2 = cursor.getCubeJustBeforePosition();
		computePreview();
	}
}

void Tool_Shape_TwoCorners::onLeftClicDown(const Cursor& cursor) {
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

void Tool_Shape_TwoCorners::onRightClicDown(const Cursor& cursor) {
	if (m_bFirstCornerSelected) {
		removeCubes();
		m_bFirstCornerSelected = false;
		m_previewGroup.removeAllCubes();
	}
}

void Tool_Shape_TwoCorners::onKeyPressed(SpecialKey key) {
	if (key == SPACE && m_bFirstCornerSelected) {
		replaceMaterials();
		m_bFirstCornerSelected = false;
		m_previewGroup.removeAllCubes();
	}
}

void Tool_Shape_TwoCorners::computeBoundingBox() {
	m_bbox = BoundingBox(m_corner1, m_corner2, CORNERS);
}