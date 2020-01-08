#pragma once

#include "Function.hpp"

class Function_Inverse : public Function {
public:
	Function_Inverse();
	~Function_Inverse() = default;

	float eval(float d) const override;
	bool ImGui_Parameters() override;

private:
	Uniform<float> m_power;
};