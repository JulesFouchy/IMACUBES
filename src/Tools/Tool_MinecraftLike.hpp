#pragma once

#include "Tool.hpp"

class Tool_MinecraftLike : public Tool {
public:
	Tool_MinecraftLike() = default;
	~Tool_MinecraftLike() = default;

	void onLeftClicDown (const Cursor& cursor) override;
	void onRightClicDown(const Cursor& cursor) override;
};