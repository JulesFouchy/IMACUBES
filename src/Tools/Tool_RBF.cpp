#include "Tool_RBF.hpp"

#include "Debugging/Log.hpp"

#include "RBF/RBF.hpp"

#include <imgui/imgui.h>

Function* Tool_RBF::m_modulingFunction(&Tool_RBF::m_quasiIdentity);
Function_Gaussian Tool_RBF::m_gaussian;
Function_Inverse Tool_RBF::m_inverse;
Function_QuasiIdentityMinOne Tool_RBF::m_quasiIdentity;
Function_Identity Tool_RBF::m_identity;

Tool_RBF::Tool_RBF() 
	: m_bInvertSelection(false), m_threshhold(0.1f), m_bSurfaceMode(true), m_modulingFunctionID(2)
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
	if (m_bSurfaceMode)
		return abs(d) < m_threshhold;
	else
		return d < m_threshhold;
}

void Tool_RBF::applyOnShape(std::function<void(const glm::ivec3 & pos)> whatToDoWithPos) {
	switch (m_modulingFunctionID) {
	case 0:
		m_modulingFunction = &m_gaussian;
		break;
	case 1:
		m_modulingFunction = &m_inverse;
		break;
	case 2:
		m_modulingFunction = &m_quasiIdentity;
		break;
	case 3:
		m_modulingFunction = &m_identity;
		break;
	default:
		spdlog::error("[Tool_RBF::applyOnShape] unknown phi id");
		break;
	}

	RBF rbf(m_anchorPts, m_valuesAtAnchorPts, *m_modulingFunction);

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

	ImGui::Text("Moduling function");
	bComputePreview |= ImGui::Combo("Moduling function", &m_modulingFunctionID, "Gaussian\0Inverse\0Quasi Identity\0Identity\0\0");
	bComputePreview |= m_modulingFunction->ImGui_Parameters();

	ImGui::Separator();
	ImGui::Text("Condition");
	bComputePreview |= ImGui::SliderFloat("Threshhold", &m_threshhold, 0.0f, 1.0f);
	bComputePreview |= ImGui::Checkbox("Surface only", &m_bSurfaceMode);

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

	bComputePreview |= ImGui::Checkbox("Invert Selection", &m_bInvertSelection);
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