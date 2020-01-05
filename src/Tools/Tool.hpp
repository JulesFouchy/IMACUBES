#pragma once

#include "Cursor/Cursor.hpp"

class Tool {
public:
	Tool();
	~Tool() = default;

	virtual void onLeftClicDown (const Cursor& cursor) {}
	virtual void onRightClicDown(const Cursor& cursor) {}

private:

};