#pragma once

#include "Cursor/Cursor.hpp"
#include "OpenGL/CubesGroup_WithoutMaterialIndices.hpp"

class Tool {
public:
	Tool() = default;
	static void Initialize();
	virtual ~Tool() = default;

	void showPreview();
	virtual void update(const Cursor& cursor) {}

	virtual void onLeftClicDown (const Cursor& cursor) {}
	virtual void onRightClicDown(const Cursor& cursor) {}
	virtual void onWheelScroll(int dl) {}

protected:
	CubesGroup_WithoutMaterialIndices m_previewGroup;
private:
	static size_t m_shaderLID;
};