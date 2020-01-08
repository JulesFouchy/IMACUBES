#include "Tool_RBF.hpp"

#include "Debugging/Log.hpp"

#include "RBF/Rbf.hpp"

#include "CubesMap/BoundingBox.hpp"

#include <imgui/imgui.h>

Tool_RBF::Tool_RBF() 
	: m_bInvertSelection(false), m_threshhold(0.1f), m_selectedPhiID(0)
{}

void Tool_RBF::onLeftClicDown(const Cursor& cursor) {
	addCubeToSelection(cursor.getCubeJustBeforePosition(), 0.0f);
	computePreview();
}

void Tool_RBF::update(const Cursor& cursor) {
	ImGui_Window();
}

void Tool_RBF::addCubeToSelection(const glm::vec3& positionPt, double valueAtAnchorPoint) {
	m_anchorPts.push_back(positionPt);
	m_valuesAtAnchorPts.conservativeResize(m_valuesAtAnchorPts.size() + 1);
	m_valuesAtAnchorPts(m_valuesAtAnchorPts.size() - 1) = valueAtAnchorPoint;
}

bool Tool_RBF::condition(float d) {
	return d < m_threshhold;
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
		if ((!m_bInvertSelection && condition(d)) || (m_bInvertSelection && !condition(d))) {
			whatToDoWithPos(pos);
		}
	}
}

void Tool_RBF::reset() {
	m_anchorPts.clear();
	m_valuesAtAnchorPts.resize(0);
	m_previewGroup.removeAllCubes();
}

void Tool_RBF::ImGui_Window() {
	ImGui::Begin("RBF distance field");
	bool bComputePreview = false;

	bComputePreview |= ImGui::Combo("Moduling function", &m_selectedPhiID, "Gaussian\0Multi-Quadratic\0Inverse Multi-Quadratic\0\0");
	ImGui::Separator();
	bComputePreview |= ImGui::SliderFloat("Threshhold", &m_threshhold, 0.0f, 1.0f);
	bComputePreview |= ImGui::SliderFloat("Growth speed", &vitesse_decroissance, 0.0, 1.0);

	bComputePreview |= ImGui::Checkbox("Invert Selection", &m_bInvertSelection);

	ImGui::Separator();
	for (size_t k = 0; k < m_anchorPts.size(); ++k) {
		glm::vec3& anchorPt = m_anchorPts[k];
		float& value = m_valuesAtAnchorPts[k];
		ImGui::PushID(k);
		bComputePreview |= ImGui::DragFloat3("Pos", &anchorPt.x);
		bComputePreview |= ImGui::DragFloat("Val", &value);
		ImGui::PopID();
		ImGui::Separator();
	}

	if (ImGui::Button("Add")) {
		addCubes();
	}
	ImGui::SameLine();
	if (ImGui::Button("Remove")) {
		removeCubes();
	}
	ImGui::SameLine();
	if (ImGui::Button("Paint")) {
		replaceMaterials();
	}
	if (ImGui::Button("Reset")) {
		reset();
	}


	if (bComputePreview)
		computePreview();

	ImGui::End();
}