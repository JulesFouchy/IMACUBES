#pragma once

#include "Tool_Shape.hpp"

class Tool_BoxTwoCorners : public Tool_Shape {
public:
	Tool_BoxTwoCorners();
	~Tool_BoxTwoCorners() = default;

	void update(const Cursor& cursor) override;

	void onLeftClicDown(const Cursor& cursor) override;
	void onRightClicDown(const Cursor& cursor) override;
	void onKeyPressed(SpecialKey key) override;

private:
	void applyOnShape(std::function<void(const glm::ivec3 & pos)> whatToDoWithPos) override;

private:
	glm::ivec3 m_corner1;
	glm::ivec3 m_corner2;
	bool m_bFirstCornerSelected;
};