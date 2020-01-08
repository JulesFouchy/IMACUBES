# include "Function_QuasiIdentityMinOne.hpp"

Function_QuasiIdentityMinOne::Function_QuasiIdentityMinOne()
	: m_power("Power", HistoryType::Tools, 2.0f, 0.0f, 6.0f)
{}

float Function_QuasiIdentityMinOne::eval(float x) const {
	return pow(1.0f + pow(m_growthSpeed.getValue() * x, m_power.getValue()), 1.0f/m_power.getValue());
}

bool Function_QuasiIdentityMinOne::ImGui_Parameters() {
	bool b = false;
	b |= Function::ImGui_Parameters();
	b |= m_power.ImGui_Slider();
	return b;
}