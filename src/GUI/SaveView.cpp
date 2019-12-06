#include "SaveView.hpp"

#include "imgui/imgui.h"
#include "Helper/Display.hpp"
#include "OpenGL/FrameBuffer.hpp"

#include "App.hpp"

PopupWindow_SaveView::PopupWindow_SaveView()
	: PopupWindow("Saving current view"),
	  m_widthHeightRatioPicker(),
	  m_filepathPicker(" PNG (*.png)\0*.png;*.PNG\0All Files (*.*)\0*.*\0")
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
	ConfirmationButton();
	EndWindow();
}

void PopupWindow_SaveView::OnConfirmation() {
	FrameBuffer saveBuffer(m_widthHeightRatioPicker.getWidth(), m_widthHeightRatioPicker.getHeight());
	saveBuffer.bind();
	saveBuffer.clear();
	App::Get().drawScene();
	saveBuffer.save(m_filepathPicker.getFilepath());
	saveBuffer.unbind();
}