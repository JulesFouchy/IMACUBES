#pragma once

#include "GUI/PopupWindow/_PopupWindow.hpp"

class Tool_RBF;

class PopupWindow_RBF : public PopupWindow {
public:
	PopupWindow_RBF(Tool_RBF* parent);
	~PopupWindow_RBF() = default;

	void Show() override;
private:
	void OnConfirmation() override;

private:
	Tool_RBF* m_parent;
};