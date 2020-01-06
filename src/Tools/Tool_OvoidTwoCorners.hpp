#pragma once

#include "Tool_Shape_TwoCorners.hpp"

class Tool_OvoidTwoCorners : public Tool_Shape_TwoCorners {
public:
	Tool_OvoidTwoCorners() = default;
	~Tool_OvoidTwoCorners() = default;

private:
	void applyOnShape(std::function<void(const glm::ivec3 & pos)> whatToDoWithPos) override;
};
