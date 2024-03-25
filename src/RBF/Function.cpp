#include "Function.hpp"
#include <imgui/imgui.h>

Function::Function()
    : m_growthSpeed("Growth speed", HistoryType::Tools, 0.5f, 0.0f, 1.0f)
{}

bool Function::ImGui_Parameters()
{
    bool b = false;
    b |= m_growthSpeed.ImGui_Slider();
    return b;
}