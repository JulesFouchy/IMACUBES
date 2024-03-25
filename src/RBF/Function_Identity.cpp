#include "Function_Identity.hpp"

float Function_Identity::eval(float x) const
{
    return x * m_growthSpeed.getValue();
}

bool Function_Identity::ImGui_Parameters()
{
    bool b = false;
    b |= Function::ImGui_Parameters();
    return b;
}