#pragma once

#include "Tool.hpp"

#include <glm/glm.hpp>

class Tool_Sphere : public Tool {
public:
	Tool_Sphere();
	~Tool_Sphere() = default;

	void onLeftClicDown(const Cursor& cursor) override;

private:
	void generateSphere();

private:
	bool m_bCenterSelected;

	glm::ivec3 m_center;
	int m_radius;
};