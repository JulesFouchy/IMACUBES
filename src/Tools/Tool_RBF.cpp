#include "Tool_RBF.hpp"

#include "Debugging/Log.hpp"

#include "RBF/Rbf.hpp"

#include "CubesMap/BoundingBox.hpp"

#include <imgui/imgui.h>

Tool_RBF::Tool_RBF() 
	: m_selectedPhiID(0)
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

void Tool_RBF::reset() {
	m_anchorPts.clear();
	m_valuesAtAnchorPts.resize(0);
	m_previewGroup.removeAllCubes();
}

void Tool_RBF::ImGui_Window() {
	ImGui::Begin("RBF distance field");
	bool bComputePreview = false;
	//
	bComputePreview |= ImGui::Combo("Moduling function", &m_selectedPhiID, "Gaussian\0Multi-Quadratic\0Inverse Multi-Quadratic\0\0");

	for (size_t k = 0; k < m_anchorPts.size(); ++k) {
		glm::vec3& anchorPt = m_anchorPts[k];
		float& value = m_valuesAtAnchorPts[k];
		ImGui::PushID(k);
		bComputePreview |= ImGui::DragFloat3("Pos", &anchorPt.x);
		bComputePreview |= ImGui::DragFloat("Val", &value);
		ImGui::PopID();
		ImGui::Separator();
	}

	ImGui::SliderFloat("Growth speed", &vitesse_decroissance, 0.0, 1.0);

	if (bComputePreview)
		computePreview();
	static bool inv = false;
	ImGui::Checkbox("Invert Selection", &inv);
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

	ImGui::End();
}