#pragma once

#include <string>

enum class OpenGLType {
    Int,
    Float,
    Vec2,
    Vec3,
    Vec4,
};

namespace GLType {
OpenGLType FromString(const std::string& s_type);
}