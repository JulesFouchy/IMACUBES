#include <imgui/imgui.h>
#include "GUI/PopupWindow/_PopupWindow.hpp"
#include "Tool_RBF_Window.hpp"
#include "Tools/Tool_RBF.hpp"
#include "Locator/Locate.hpp"



PopupWindow_RBF::PopupWindow_RBF(Tool_RBF* parent)
	: PopupWindow("RBF distance field"), m_parent(parent)
{}

void PopupWindow_RBF::Show() {
	BeginWindow();
	bool bComputePreview = false;
	//
	bComputePreview |= ImGui::Combo("Moduling function", &m_parent->m_selectedPhiID, "Gaussian\0Multi-Quadratic\0Inverse Multi-Quadratic\0\0");

	for (size_t k = 0; k < m_parent->m_anchorPts.size(); ++k) {
		glm::vec3& anchorPt = m_parent->m_anchorPts[k];
		float& value = m_parent->m_valuesAtAnchorPts[k];
		ImGui::PushID(k);
		bComputePreview |= ImGui::DragFloat3("Pos", &anchorPt.x);
		bComputePreview |= ImGui::DragFloat("Val", &value);
		ImGui::PopID();
		ImGui::Separator();
	}

	ImGui::SliderFloat("Growth speed", &m_parent->vitesse_decroissance, 0.0, 1.0);

	if (bComputePreview)
		m_parent->computePreview();

	ConfirmationButton();

	EndWindow();
}


void PopupWindow_RBF::OnConfirmation() {
	m_parent->addCubes();
	m_parent->m_anchorPts.clear();
	m_parent->m_valuesAtAnchorPts.resize(0);
	m_parent->m_previewGroup.removeAllCubes();
}

