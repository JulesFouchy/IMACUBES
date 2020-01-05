#pragma once

#include "Tool.hpp"

#include <functional>

class Tool_Shape : public Tool {
public:
	Tool_Shape() = default;
	virtual ~Tool_Shape() = default;

	void onLeftClicDown(const Cursor& cursor) override;
	void onRightClicDown(const Cursor& cursor) override;

protected:
	virtual void applyOnShape(std::function<void(const glm::ivec3 & pos)> whatToDoWithPos) = 0;

	void addCubes();
	void removeCubes();
	void computePreview();
};