#pragma once

#include "Tool_Shape.hpp"

#include <glm/glm.hpp>


class Tool_Sphere : public Tool_Shape {
public:
	Tool_Sphere();
	~Tool_Sphere() = default;

	void update(const Cursor& cursor) override;

	void onWheelScroll(int dl) override;

private:
	void applyOnShape(std::function<void(const glm::ivec3 & pos)> whatToDoWithPos) override;

private:
	glm::ivec3 m_center;
	int m_radius;
};