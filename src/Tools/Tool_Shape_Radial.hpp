#pragma once

#include "Tool_Shape.hpp"

class Tool_Shape_Radial : public Tool_Shape {
public:
	Tool_Shape_Radial();
	~Tool_Shape_Radial() = default;

	void update(const Cursor & cursor) override;

	void onWheelScroll(int dl) override;

protected:
	void computeBoundingBox();

protected:
	glm::ivec3 m_center;
	glm::ivec3 m_radiuses;
};