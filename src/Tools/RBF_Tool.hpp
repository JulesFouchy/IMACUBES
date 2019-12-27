#pragma once
#include "GUI/PopupWindow/_PopupWindow.hpp"

class PopupWindow_RBF : public PopupWindow {
public:
	PopupWindow_RBF();
	~PopupWindow_RBF() = default;

	void Open() override;
private:
	void Show() override;
	void OnConfirmation() override;
};