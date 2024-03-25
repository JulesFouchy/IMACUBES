#include "FilepathPicker.hpp"
#include "GUI/FileBrowser.hpp"
#include "imgui/imgui.h"
#include "imgui/misc/cpp/imgui_stdlib.h"

GUIwidget_FilepathPicker::GUIwidget_FilepathPicker(const char* fileFilter)
    : m_filepath(""), m_fileFilter(fileFilter)
{
}

void GUIwidget_FilepathPicker::ShowOpenfilename()
{
    ImGui::InputText("", &m_filepath);
    if (ImGui::Button("Choose file"))
    {
        std::string tmp = FileBrowser::openfilename(m_fileFilter);
        if (tmp != "")
        {
            m_filepath = tmp;
        }
    }
}

void GUIwidget_FilepathPicker::ShowSavefilename()
{
    ImGui::InputText("", &m_filepath);
    if (ImGui::Button("Choose destination"))
    {
        std::string tmp = FileBrowser::savefilename(m_fileFilter);
        if (tmp != "")
        {
            m_filepath = tmp;
        }
    }
}