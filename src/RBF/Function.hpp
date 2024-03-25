#pragma once

#include "OpenGL/Uniform/Uniform.hpp"

class Function {
public:
    Function();
    ~Function() = default;

    virtual float eval(float d) const = 0;
    virtual bool  ImGui_Parameters();

protected:
    Uniform<float> m_growthSpeed;
};