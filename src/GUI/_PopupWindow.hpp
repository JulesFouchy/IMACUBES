#pragma once

#include <string>

class PopupWindow {
// Functions to override
public:
	virtual void Open();
protected:
	virtual void Show() = 0;
	virtual void OnConfirmation() = 0;

// Base functions
public:
	void Show_IfOpen();
protected:
	PopupWindow(const std::string& windowName);
	~PopupWindow() = default;

	void BeginWindow();
	void ConfirmationButton();
	void EndWindow();

protected:
	bool m_bMustShow;
private:
	std::string m_name;
};