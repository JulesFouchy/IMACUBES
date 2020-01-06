#pragma once

#include "Tool_Shape.hpp"

class Tool_Shape_TwoCorners : public Tool_Shape {
public:
	Tool_Shape_TwoCorners();
	~Tool_Shape_TwoCorners() = default;

	void update(const Cursor & cursor) override;

	void onLeftClicDown(const Cursor & cursor) override;
	void onRightClicDown(const Cursor & cursor) override;
	void onKeyPressed(SpecialKey key) override;

protected:
	void computeBoundingBox();

protected:
	glm::ivec3 m_corner1;
	glm::ivec3 m_corner2;
	bool m_bFirstCornerSelected;
};