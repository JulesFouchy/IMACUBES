#include <imgui/imgui.h>
#include "GUI/PopupWindow/_PopupWindow.hpp"
#include "Tool_RBF_Window.hpp"
#include "Tools/Tool_RBF.hpp"
#include "Locator/Locate.hpp"



PopupWindow_RBF::PopupWindow_RBF(Tool_RBF* parent)
	: PopupWindow("RBF_Tool"), m_parent(parent)
{
}

void PopupWindow_RBF::Open() {
	PopupWindow::Open();
}




void PopupWindow_RBF::Show() {
	ImGui::SetNextWindowPos(ImVec2(0, 100), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(1000, 680), ImGuiCond_FirstUseEver);
	BeginWindow();
	//
	ImGui::Separator();
	//
	ImGui::Text("Choose RBF: "); ImGui::SameLine();
	//
	ImGui::Separator();

	//ImGui::SliderFloat("Vitesse de décroissance", &m_parent->vitesse_decroissance, 0.0, 1.0);

	//Selection de la fonction RBF
	ImGui::Combo("phi",&m_parent->m_selectedPhi, " Gaussienne\0 Multi-quadratique\0inverse Multi-quadratique\0\0");
	
	ConfirmationButton();
	EndWindow();
}


void PopupWindow_RBF::OnConfirmation() {
	m_parent->addCubes();
}

