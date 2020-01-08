#pragma once
#include "GUI/PopupWindow/_PopupWindow.hpp"


class Tool_RBF;

class PopupWindow_RBF : public PopupWindow {
public:
	PopupWindow_RBF(Tool_RBF* parent);
	~PopupWindow_RBF() = default;

	void Open() override;



private:
	void Show() override;
	void OnConfirmation() override;
	Tool_RBF* m_parent;
};