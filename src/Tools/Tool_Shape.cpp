#include "Tool_Shape.hpp"

#include "Locator/Locate.hpp"
#include "CubesMap/CubesMap.hpp"
#include "History/History.hpp"

void Tool_Shape::addCubes() {
	History& history = Locate::history(HistoryType::Cubes);
	history.beginUndoGroup();
	applyOnShape([](const glm::ivec3& pos) {Locate::cubesMap().addCube(pos); });
	history.endUndoGroup();
}

void Tool_Shape::removeCubes() {
	History& history = Locate::history(HistoryType::Cubes);
	history.beginUndoGroup();
	applyOnShape([](const glm::ivec3& pos) {Locate::cubesMap().removeCube(pos); });
	history.endUndoGroup();
}

void Tool_Shape::computePreview() {
	m_previewGroup.removeAllCubes();
	applyOnShape([this](const glm::ivec3& pos) {this->m_previewGroup.addCube_NoExistenceCheck(pos); });
}

void Tool_Shape::onLeftClicDown(const Cursor& cursor) {
	addCubes();
}

void Tool_Shape::onRightClicDown(const Cursor& cursor) {
	removeCubes();
}