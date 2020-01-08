#include "Function_Gaussian.hpp"

#include "Helper/Maths.hpp"

Function_Gaussian::Function_Gaussian()
	: m_power("Power", HistoryType::Tools, 2.0f, 0.0f, 6.0f)
{}

float Function_Gaussian::eval(float x) const {
	return exp(-pow(abs(x * m_growthSpeed.getValue()), m_power.getValue()));
}

bool Function_Gaussian::ImGui_Parameters() {
	bool b = false;
	b |= Function::ImGui_Parameters();
	b |= m_power.ImGui_Slider();
	return b;
}