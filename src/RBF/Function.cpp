#include "Function.hpp"

#include <imgui/imgui.h>

Function::Function()
	: m_growthSpeed("Growth speed", HistoryType::Tools, 1.0f, 0.0f, 10.0f)
{}

bool Function::ImGui_Parameters() {
	bool b = false;
	b |= m_growthSpeed.ImGui_Slider();
	return b;
}