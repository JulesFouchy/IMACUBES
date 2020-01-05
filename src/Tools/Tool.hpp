#pragma once

#include "Cursor/Cursor.hpp"
#include "OpenGL/CubesGroup_WithoutMaterialIndices.hpp"

class Tool {
public:
	Tool() = default;
	~Tool() = default;

	void showPreview();
	virtual void update(const Cursor& cursor) {}

	virtual void onLeftClicDown (const Cursor& cursor) {}
	virtual void onRightClicDown(const Cursor& cursor) {}
	virtual void onWheelScroll(int dl) {}

protected:
	CubesGroup_WithoutMaterialIndices m_previewGroup;
};