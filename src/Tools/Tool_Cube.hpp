#pragma once

#include "Tool_Shape.hpp"

class Tool_Cube : public Tool_Shape {
public:
	Tool_Cube();
	~Tool_Cube() = default;

	void update(const Cursor& cursor) override;

	void onWheelScroll(int dl) override;

private:
	void applyOnShape(std::function<void(const glm::ivec3 & pos)> whatToDoWithPos) override;

private:
	glm::ivec3 m_center;
	int m_radius;
};