#include "Tool_RBF.hpp"
#include "Debugging/Log.hpp"


Tool_RBF::Tool_RBF() 
	: m_window(this)
{
	m_window.Open();
}

void Tool_RBF::showGUI() {
	m_window.Show_IfOpen();
	m_group.draw();
}


void Tool_RBF::addCubeToSelection(const glm::vec3& positionPt, const double valueAtAnchorPoint){
	m_anchorPts.push_back(positionPt);
	spdlog::info("x : {} y : {}  z : {}", positionPt.x, positionPt.y, positionPt.z);
	m_valuesAtAnchorPts.conservativeResize(m_valuesAtAnchorPts.size() + 1);
	m_valuesAtAnchorPts(m_valuesAtAnchorPts.size() - 1) = valueAtAnchorPoint;

	m_group.addCube(positionPt);
}

void Tool_RBF::onLeftClick(const Cursor& cursor) {
	static double val = -2;
	val += 1;

	addCubeToSelection(cursor.getCubeJustBeforePosition(), val);

}

