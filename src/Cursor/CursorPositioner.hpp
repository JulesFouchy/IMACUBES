#pragma once

class Cursor;

class CursorPositioner {
public:
	CursorPositioner(Cursor* cursor)
		: m_cursor(cursor) {}
	~CursorPositioner() = default;

	virtual void computePosition() = 0;

protected:
	Cursor* m_cursor;
};