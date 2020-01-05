#pragma once

#include "CursorPositioner.hpp"

class CursorPositioner_OnHoveredCube : public CursorPositioner {
public:
	CursorPositioner_OnHoveredCube(Cursor* cursor);
	~CursorPositioner_OnHoveredCube() = default;

	void computePosition() override;
};