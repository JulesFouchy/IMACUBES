#include <imgui/imgui.h>
#include "GUI/MoreImGui.hpp"
#include "Helper/Display.hpp"
#include "Helper/File.hpp"
#include "OpenGL/SaveBufferMultisampled.hpp"
#include "GUI/PopupWindow/_PopupWindow.hpp"
#include "RBF_Tool.hpp"

#include "App.hpp"

PopupWindow_RBF::PopupWindow_RBF()
	: PopupWindow("RBF_Tool")
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
	//
	ConfirmationButton(); ImGui::SameLine();
	//
	EndWindow();
}

void PopupWindow_RBF::OnConfirmation() {
  //LANCER CALCUL RBF

}