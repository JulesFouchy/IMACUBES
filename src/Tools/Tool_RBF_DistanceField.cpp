#include "Tool_RBF_DistanceField.hpp"

#include "RBF/RBF.hpp"

Tool_RBF_DistanceField::Tool_RBF_DistanceField() 
{}

void Tool_RBF_DistanceField::addCubeToSelection(const glm::vec3& pos) {
	m_anchorPts.push_back(pos);
	m_valuesAtAnchorPts.conservativeResize(m_valuesAtAnchorPts.size() + 1);
	m_valuesAtAnchorPts(m_valuesAtAnchorPts.size() - 1) = 0.5f;
}

void Tool_RBF_DistanceField::evaluateRBFOnWorld(std::function<void(const glm::ivec3 & pos)> whatToDoWithPos){
	RBF rbf = RBF(m_anchorPts, m_valuesAtAnchorPts, *m_modulingFunction);
	BoundingBox worldBB;
	for (const glm::ivec3& pos : worldBB) {
		float d = rbf.eval(pos);
		if ((!m_bInvertSelection && condition(d)) || (m_bInvertSelection && !condition(d))) {
			whatToDoWithPos(pos);
		}
	}
}

bool Tool_RBF_DistanceField::condition(float d) {
	if (m_bSurfaceMode)
		return abs(d) < m_threshhold;
	else
		return d < m_threshhold;
}

void Tool_RBF_DistanceField::reset() {
	Tool_RBF::reset();
	m_anchorPts.clear();
}

void Tool_RBF_DistanceField::ImGui_Window() {
	ImGui::Begin("RBF distance field");
	bool bComputePreview = false;

	bComputePreview |= ImGui_ModulingFunction();
	ImGui::Separator();

	bComputePreview |= ImGui_Condition();
	ImGui::Separator();

	ImGui::Text("Anchor points");
	for (size_t k = 0; k < m_anchorPts.size(); ++k) {
		glm::vec3& anchorPt = m_anchorPts[k];
		float& value = m_valuesAtAnchorPts[k];
		ImGui::PushID(k);
		bComputePreview |= ImGui::DragFloat3("Pos", &anchorPt.x);
		bComputePreview |= ImGui::DragFloat("Val", &value);
		ImGui::PopID();
		ImGui::Separator();
	}

	ImGui_Finalize(bComputePreview);

	ImGui::End();
}