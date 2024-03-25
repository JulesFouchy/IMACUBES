#pragma once

#include "Function.hpp"

class Function_Identity : public Function {
public:
    Function_Identity()  = default;
    ~Function_Identity() = default;

    float eval(float x) const override;
    bool  ImGui_Parameters() override;
};