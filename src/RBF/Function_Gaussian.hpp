#pragma once

#include "Function.hpp"

class Function_Gaussian : public Function {
public:	
	Function_Gaussian();
	~Function_Gaussian() = default;

	float eval(float x) const override;
	bool ImGui_Parameters() override;

private:
	Uniform<float> m_power;
};