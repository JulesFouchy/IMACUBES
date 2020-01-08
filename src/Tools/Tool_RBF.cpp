#include "Tool_RBF.hpp"

#include "Debugging/Log.hpp"

#include "RBF/Rbf.hpp"

#include "CubesMap/BoundingBox.hpp"

Tool_RBF::Tool_RBF() 
	: m_window(this), m_selectedPhiID(0)
{}

void Tool_RBF::onLeftClicDown(const Cursor& cursor) {
	static double val = -2;
	val += 1;

	addCubeToSelection(cursor.getCubeJustBeforePosition(), val);
	computePreview();
}

void Tool_RBF::update(const Cursor& cursor) {
	m_window.Show();
}

void Tool_RBF::addCubeToSelection(const glm::vec3& positionPt, double valueAtAnchorPoint) {
	m_anchorPts.push_back(positionPt);
	spdlog::info("x : {} y : {}  z : {}", positionPt.x, positionPt.y, positionPt.z);
	m_valuesAtAnchorPts.conservativeResize(m_valuesAtAnchorPts.size() + 1);
	m_valuesAtAnchorPts(m_valuesAtAnchorPts.size() - 1) = valueAtAnchorPoint;
}

void Tool_RBF::applyOnShape(std::function<void(const glm::ivec3 & pos)> whatToDoWithPos) {
	std::function<double(double)> phi;
	switch (m_selectedPhiID) {
	case 0:
		phi = [this](float x) { return gaussian(x, this->vitesse_decroissance); };
		break;
	case 1:
		phi = &multiQuadra;
		break;
	case 2:
		phi = &invMultiQuadra;
		break;
	default:
		spdlog::error("[PopupWindow_RBF::OnConfirmation] Unknown phi");
		break;
	}

	RBF rbf(m_anchorPts, m_valuesAtAnchorPts, phi);

	BoundingBox worldBB;
	for (const glm::ivec3& pos : worldBB) {
		float d = rbf.eval(pos);
		if (d < 0.1) {
			whatToDoWithPos(pos);
		}
	}


}