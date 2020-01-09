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
	addCubeToSelection(cursor.getCubeJustBeforePosition());
	computePreview();
}

void Tool_RBF::update(const Cursor& cursor) {
	ImGui_Window();
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
	evaluateRBFOnWorld(whatToDoWithPos);
}

void Tool_RBF::reset() {
	m_valuesAtAnchorPts.resize(0);
	m_previewGroup.removeAllCubes();
}

bool Tool_RBF::ImGui_ModulingFunction() {
	bool b = false;
	ImGui::Text("Moduling function");
	b |= ImGui::Combo("Moduling function", &m_modulingFunctionID, "Gaussian\0Inverse\0Quasi Identity\0Identity\0\0");
	b |= m_modulingFunction->ImGui_Parameters();
	return b;
}

bool Tool_RBF::ImGui_Condition() {
	bool b = false;
	ImGui::Text("Condition");
	b |= ImGui::SliderFloat("Threshhold", &m_threshhold, 0.0f, 1.0f);
	b |= ImGui::Checkbox("Surface only", &m_bSurfaceMode);
	return b;
}

void Tool_RBF::ImGui_Finalize(bool bComputePreview){
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
}