#include "Function_Inverse.hpp"

Function_Inverse::Function_Inverse()
    : m_power("Power", HistoryType::Tools, 2.0f, 0.0f, 6.0f)
{}

float Function_Inverse::eval(float x) const
{
    return 1.0f / (1.0f + pow(x * m_growthSpeed.getValue(), m_power.getValue()));
}

bool Function_Inverse::ImGui_Parameters()
{
    bool b = false;
    b |= Function::ImGui_Parameters();
    b |= m_power.ImGui_Slider();
    return b;
}