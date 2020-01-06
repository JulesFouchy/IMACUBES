#include "History.hpp"

#include "Debugging/Log.hpp"

History::History(const std::string& name)
	: m_index(-1), m_indexOfCumulfNbOfActions(-1), m_name(name)
{
}

void History::beginUndoGroup() {
	//spdlog::info("begin undo group");
	m_tmpActionBuffer.resize(0);
}

void History::endUndoGroup() {
	//spdlog::info("end undo group");
	if (m_tmpActionBuffer.size() > 0) {
		//
		m_cumulNbOfActionsToGetToThisUndoGroup.resize(m_indexOfCumulfNbOfActions + 1);
		m_cumulNbOfActionsToGetToThisUndoGroup.push_back(m_tmpActionBuffer.size()+ (m_indexOfCumulfNbOfActions>-1 ? m_cumulNbOfActionsToGetToThisUndoGroup[m_indexOfCumulfNbOfActions] : 0));
		m_indexOfCumulfNbOfActions++;
		//
		m_actions.resize(m_indexOfCumulfNbOfActions>0 ? m_cumulNbOfActionsToGetToThisUndoGroup[m_indexOfCumulfNbOfActions-1] : 0);
		for (size_t i = 0; i < m_tmpActionBuffer.size(); ++i) {
			m_actions.push_back(m_tmpActionBuffer[i]);
			m_index++;
		}
	}
#ifndef NDEBUG
	else {
		spdlog::warn("Empty undo group");
	}
#endif
}

void History::addAction(Action action) {
	//spdlog::info("add action");
	m_tmpActionBuffer.push_back(action);
}

void History::moveBackward() {
	if (m_indexOfCumulfNbOfActions > -1) {
		//spdlog::info("moving backward");
		for (int i = 0; i < nbOfActionsBetweenThisAndPreviousUndoGroup(m_indexOfCumulfNbOfActions); ++i) {
			m_actions[m_index].Undo();
			m_index--;
		}
		m_indexOfCumulfNbOfActions--;
	}
}

void History::moveForward() {
	if (m_indexOfCumulfNbOfActions < (int)(m_cumulNbOfActionsToGetToThisUndoGroup.size() - 1)) { // cast to an int because size_t is an unsigned type and it causes a bug when m_indexOfCumulfNbOfActions == -1
		//spdlog::info("moving forward");
		for (int i = 0; i < nbOfActionsBetweenThisAndPreviousUndoGroup(m_indexOfCumulfNbOfActions+1); ++i) {
			m_index++;
			m_actions[m_index].Do();
		}
		m_indexOfCumulfNbOfActions++;
	}
}

unsigned int History::nbOfActionsBetweenThisAndPreviousUndoGroup(int index){
	return m_cumulNbOfActionsToGetToThisUndoGroup[index] - (index > 0 ? m_cumulNbOfActionsToGetToThisUndoGroup[index-1] : 0);
}