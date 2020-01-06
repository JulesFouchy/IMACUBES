#pragma once

#include "Tool_Shape.hpp"

class Tool_OvoidTwoCorners : public Tool_Shape {
public:
	Tool_OvoidTwoCorners();
	~Tool_OvoidTwoCorners() = default;

	void update(const Cursor& cursor) override;

	void onLeftClicDown(const Cursor& cursor) override;
	void onRightClicDown(const Cursor& cursor) override;

private:
	void applyOnShape(std::function<void(const glm::ivec3 & pos)> whatToDoWithPos) override;

	float normalizedDistance2D(const glm::ivec3& v0, const glm::ivec3& v1, const glm::ivec3& size, int c0, int c1);

private:
	glm::ivec3 m_corner1;
	glm::ivec3 m_corner2;
	bool m_bFirstCornerSelected;
};
