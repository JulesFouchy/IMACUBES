#include <imgui/imgui.h>
#include "GUI/PopupWindow/_PopupWindow.hpp"
#include "Tool_RBF_Window.hpp"
#include "RBF/Rbf.hpp"
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
	BeginWindow();
	//
	ImGui::Separator();
	//
	ImGui::Text("Choose RBF: "); ImGui::SameLine();
	//
	ImGui::Separator();

	//Selection de la fonction RBF
	static int item_current = 1;
	ImGui::Combo("phi",&item_current, " Gaussienne\0 quadratique\0 Multi-quadratique\0 inverse Multi-quadratique\0\0");
	ConfirmationButton();
	EndWindow();
}

void PopupWindow_RBF::OnConfirmation() {
	//pseudo

	//RBF rbf(m_parent->m_anchorPts, m_parent->m_valuesAtAnchorPts);
	//for( const glm::vec3& : Locate::cubesMap())


}