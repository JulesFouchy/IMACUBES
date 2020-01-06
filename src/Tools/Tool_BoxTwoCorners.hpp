#pragma once

#include "Tool_Shape_TwoCorners.hpp"

class Tool_BoxTwoCorners : public Tool_Shape_TwoCorners {
public:
	Tool_BoxTwoCorners() = default;
	~Tool_BoxTwoCorners() = default;

private:
	void applyOnShape(std::function<void(const glm::ivec3 & pos)> whatToDoWithPos) override;
};