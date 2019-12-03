#pragma once

#include <functional>

class Action{
public:
	Action();
	Action(std::function<void(void)> howToDo, std::function<void(void)> howToUndo);
	~Action();
	inline void Do() { m_howToDo(); }
	inline void Undo() { m_howToUndo(); }
private:
	std::function<void(void)> m_howToDo;
	std::function<void(void)> m_howToUndo;
};