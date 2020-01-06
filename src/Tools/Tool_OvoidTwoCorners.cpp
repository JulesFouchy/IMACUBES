#include "Tool_OvoidTwoCorners.hpp"

#include "CubesMap/BoundingBox.hpp"

#include "Debugging/Log.hpp"

#include "Helper/Maths.hpp"

Tool_OvoidTwoCorners::Tool_OvoidTwoCorners()
	: m_bFirstCornerSelected(false)
{}

void Tool_OvoidTwoCorners::update(const Cursor& cursor) {
	if (m_bFirstCornerSelected) {
		m_corner2 = cursor.getCubeJustBeforePosition();
		computePreview();
	}
}

void Tool_OvoidTwoCorners::onLeftClicDown(const Cursor& cursor) {
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

void Tool_OvoidTwoCorners::onRightClicDown(const Cursor& cursor) {
	if (m_bFirstCornerSelected) {
		removeCubes();
		m_bFirstCornerSelected = false;
		m_previewGroup.removeAllCubes();
	}
}

void Tool_OvoidTwoCorners::onKeyPressed(SpecialKey key) {
	if (key == SPACE && m_bFirstCornerSelected) {
		replaceMaterials();
		m_bFirstCornerSelected = false;
		m_previewGroup.removeAllCubes();
	}
}

void Tool_OvoidTwoCorners::applyOnShape(std::function<void(const glm::ivec3 & pos)> whatToDoWithPos) {
	BoundingBox bbox(m_corner1, m_corner2, CORNERS);
	int nbDimensions = (bbox.size().x != 0 ? 1 : 0)
					 + (bbox.size().y != 0 ? 1 : 0)
					 + (bbox.size().z != 0 ? 1 : 0);
	if (nbDimensions == 3) {
		for (const glm::ivec3& pos : bbox) {
			if (glm::length((glm::vec3)(pos - bbox.center()) / (glm::vec3)bbox.size()) <= 0.5f)
				whatToDoWithPos(pos);
		}
	}
	else if (nbDimensions == 2) { // to prevent divisions by 0
		int c0, c1;
		if      (bbox.size().x == 0) { c0 = 1; c1 = 2; }
		else if (bbox.size().y == 0) { c0 = 0; c1 = 2; }
		else                         { c0 = 0; c1 = 1; }
		for (const glm::ivec3& pos : bbox) {
			if (MyMaths::NormalizedDistance2D(pos, bbox.center(), bbox.size(), c0, c1) <= 0.5f)
				whatToDoWithPos(pos);
		}
	}
	else {
		for (const glm::ivec3& pos : bbox)
			whatToDoWithPos(pos);
	}
}