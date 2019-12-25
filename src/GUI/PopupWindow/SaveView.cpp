#include "SaveView.hpp"

#include <imgui/imgui.h>
#include "GUI/MoreImGui.hpp"
#include "Helper/Display.hpp"
#include "Helper/File.hpp"
#include "OpenGL/SaveBufferMultisampled.hpp"

#include "App.hpp"

PopupWindow_SaveView::PopupWindow_SaveView()
	: PopupWindow_WithConfirmationWarning("Saving current view"),
	  m_widthHeightRatioPicker(),
	  m_filepathPicker(" PNG (*.png)\0*.png;*.PNG\0All Files (*.*)\0*.*\0"),
	  m_nbSamplesForMSAA(4)
{
}

void PopupWindow_SaveView::Open() {
	PopupWindow::Open();
	m_widthHeightRatioPicker.setRatio(Display::GetRatio());
}

void PopupWindow_SaveView::Show() {
	m_widthHeightRatioPicker.setRatio(Display::GetRatio()); // update ratio each frame in case of resizing while this window is open
	BeginWindow();
	//
	m_widthHeightRatioPicker.ShowWidthHeight();
	ImGui::Separator();
	//
	ImGui::Text("Save as : "); ImGui::SameLine();
	m_filepathPicker.ShowSavefilename();
	//
	ImGui::Separator();
	//
	ConfirmationButton(); ImGui::SameLine();
	//
	static int item_current = 1;
	ImGui::SetNextItemWidth(50.0f);
	ImGui::Combo("Samples", &item_current, " 1\0 4\0 16\0\0");
	switch (item_current) {
	case(0): 
		m_nbSamplesForMSAA = 1;
		break;
	case(1):
		m_nbSamplesForMSAA = 4;
		break;
	case(2) : 
		m_nbSamplesForMSAA = 16;
		break;
	default:
		m_nbSamplesForMSAA = -1;
		break;
	}
	ImGui::SameLine(); ImGui::HelpMarker("Number of samples used by Multi Sampling to reduce aliasing");
	EndWindow();
}

void PopupWindow_SaveView::OnConfirmation() {
	SaveBufferMultisampled saveBuffer(m_widthHeightRatioPicker.getWidth(), m_widthHeightRatioPicker.getHeight(), m_nbSamplesForMSAA);
	//SaveBuffer saveBuffer(m_widthHeightRatioPicker.getWidth(), m_widthHeightRatioPicker.getHeight());
	saveBuffer.bind();
	saveBuffer.clear();
	App::Get().drawScene();
	saveBuffer.save(m_filepathPicker.getFilepath());
	saveBuffer.unbind();
}

bool PopupWindow_SaveView::WarnIf() {
	return MyFile::Exists(m_filepathPicker.getFilepath());
}

std::string PopupWindow_SaveView::WarningMessage() {
	return "This file already exists and will be overwritten : \n" + m_filepathPicker.getFilepath();
}