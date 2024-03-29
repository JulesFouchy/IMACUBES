#pragma once

#include "GUI/Widget/FilepathPicker.hpp"
#include "GUI/Widget/WidthHeightRatioPicker.hpp"
#include "_PopupWindow_WithConfirmationWarning.hpp"

class PopupWindow_SaveView : public PopupWindow_WithConfirmationWarning {
public:
    PopupWindow_SaveView();
    ~PopupWindow_SaveView() = default;

    void Open() override;

private:
    void        Show() override;
    void        OnConfirmation() override;
    bool        WarnIf() override;
    std::string WarningMessage() override;

private:
    GUIwidget_WidthHeightRatioPicker m_widthHeightRatioPicker;
    GUIwidget_FilepathPicker         m_filepathPicker;
    int                              m_nbSamplesForMSAA;
};