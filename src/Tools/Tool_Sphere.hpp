#pragma once

#include "Tool.hpp"

#include <glm/glm.hpp>

#include <functional>

class Tool_Sphere : public Tool {
public:
	Tool_Sphere();
	~Tool_Sphere() = default;

	void update(const Cursor& cursor) override;

	void onLeftClicDown (const Cursor& cursor) override;
	void onRightClicDown(const Cursor& cursor) override;
	void onWheelScroll(int dl) override;

private:
	void applyOnSphere(std::function<void(const glm::ivec3& pos)> addCube);

private:
	glm::ivec3 m_center;
	int m_radius;
};