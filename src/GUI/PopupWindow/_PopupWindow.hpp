#pragma once

#include <string>

class PopupWindow {
friend class PopupWindow_AreYouSure;
	// Functions to override
public:
	virtual void Open();
protected:
	virtual void Show() = 0;
	virtual void OnConfirmation() = 0;

	// Base functions
public:
	virtual void Show_IfOpen();
protected:
	PopupWindow(const std::string& windowName);
	~PopupWindow() = default;

	void BeginWindow();
	void ConfirmationButton();
	void EndWindow();

	virtual void Confirm(bool iAmSure = false) { OnConfirmation(); m_bMustShow = false; }; // indirection required by PopupWindow_WithConfirmationWarning to add checks

protected:
	bool m_bMustShow;
private:
	std::string m_name;
};