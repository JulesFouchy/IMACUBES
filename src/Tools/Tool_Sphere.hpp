#pragma once

#include "Tool_Shape_Radial.hpp"

class Tool_Sphere : public Tool_Shape_Radial {
public:
	Tool_Sphere() = default;
	~Tool_Sphere() = default;

private:
	void applyOnShape(std::function<void(const glm::ivec3 & pos)> whatToDoWithPos) override;

	void computeBoundingBox() override;
};