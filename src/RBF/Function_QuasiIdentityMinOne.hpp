#pragma once

#include "Function.hpp"

class Function_QuasiIdentityMinOne : public Function {
public:
	Function_QuasiIdentityMinOne();
	~Function_QuasiIdentityMinOne() = default;

	float eval(float d) const override;
	bool ImGui_Parameters() override;

private:
	Uniform<float> m_power;
};