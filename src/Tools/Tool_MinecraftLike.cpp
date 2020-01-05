#include "Tool_MinecraftLike.hpp"

#include "Locator/Locate.hpp"
#include "CubesMap/CubesMap.hpp"
#include "CubesMap/BoundingBox.hpp"
#include "History/History.hpp"

void Tool_MinecraftLike::onLeftClicDown(const Cursor& cursor){
	History& history = Locate::history(HistoryType::Cubes);
	history.beginUndoGroup();
	Locate::cubesMap().addCube(cursor.getCubeJustBeforePosition());
	history.endUndoGroup();
}

void Tool_MinecraftLike::onRightClicDown(const Cursor& cursor) {
	History& history = Locate::history(HistoryType::Cubes);
	history.beginUndoGroup();
	Locate::cubesMap().removeCube(cursor.getPosition());
	history.endUndoGroup();
}