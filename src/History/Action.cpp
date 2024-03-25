#include "Action.hpp"

Action::Action(std::function<void(void)> howToDo, std::function<void(void)> howToUndo)
    : m_howToDo(howToDo), m_howToUndo(howToUndo)
{
}

Action::Action()
    : m_howToDo(0), m_howToUndo(0)
{
}

Action::~Action()
{
}