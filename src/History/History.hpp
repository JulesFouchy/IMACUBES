#pragma once

#include <string>
#include <vector>
#include "Action.hpp"

class History {
public:
    History(const std::string& name = "History");
    ~History() = default;

    void beginUndoGroup();
    void endUndoGroup();
    void addAction(Action action);

    void moveBackward();
    void moveForward();

    inline const std::string& getName() const { return m_name; }

private:
    unsigned int nbOfActionsBetweenThisAndPreviousUndoGroup(int index);

private:
    std::vector<Action> m_actions;
    std::vector<int>    m_cumulNbOfActionsToGetToThisUndoGroup;
    std::vector<Action> m_tmpActionBuffer;
    int                 m_index;
    int                 m_indexOfCumulfNbOfActions;

    std::string m_name;
    /*
        We are always in the state m_actions[m_index] (m_index == -1 means that we are in the initial state, no action ever performed)
    */
};