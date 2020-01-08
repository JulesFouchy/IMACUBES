#include <imgui/imgui.h>
#include "GUI/PopupWindow/_PopupWindow.hpp"
#include "Tool_RBF_Window.hpp"
#include "Tools/Tool_RBF.hpp"
#include "Locator/Locate.hpp"



PopupWindow_RBF::PopupWindow_RBF(Tool_RBF* parent)
	: PopupWindow("RBF distance field"), m_parent(parent)
{
}

void PopupWindow_RBF::Show() {
	BeginWindow();
	//
	ImGui::Text("Choose RBF: "); ImGui::SameLine();
	ImGui::Combo("phi", &m_parent->m_selectedPhi, " Gaussienne\0 Multi-quadratique\0inverse Multi-quadratique\0\0");
	for (size_t k = 0; k < m_parent->m_anchorPts.size(); ++k) {
		glm::vec3& anchorPt = m_parent->m_anchorPts[k];
		float& value = m_parent->m_valuesAtAnchorPts[k];
		ImGui::DragFloat3("Pos", &anchorPt.x); ImGui::SameLine();
		ImGui::DragFloat("Val", &value);
	}

	//ImGui::SliderFloat("Vitesse de décroissance", &m_parent->vitesse_decroissance, 0.0, 1.0);

	//Selection de la fonction RBF
	
	ConfirmationButton();

	ImGui::SetNextWindowPos(ImVec2(0, 100), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(1000, 680), ImGuiCond_FirstUseEver);

	EndWindow();
}


void PopupWindow_RBF::OnConfirmation() {
	m_parent->addCubes();
}

