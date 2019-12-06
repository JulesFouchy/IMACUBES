#pragma once

#include "_PopupWindow.hpp"

#include "Widget/WidthHeightRatioPicker.hpp"
#include "Widget/FilepathPicker.hpp"

class PopupWindow_SaveView : public PopupWindow {
public:
	PopupWindow_SaveView();
	~PopupWindow_SaveView() = default;

	void Open() override;
private:
	void Show() override;
	void OnConfirmation() override;

private:
	GUIwidget_WidthHeightRatioPicker m_widthHeightRatioPicker;
	GUIwidget_FilepathPicker m_filepathPicker;
};