#include "OpenGLTypes.hpp"
#include "Debugging/Log.hpp"

OpenGLType GLType::FromString(const std::string& s_type)
{
    if (s_type == "int")
    {
        return OpenGLType::Int;
    }
    else if (s_type == "float")
    {
        return OpenGLType::Float;
    }
    else if (s_type == "vec2")
    {
        return OpenGLType::Vec2;
    }
    else if (s_type == "vec3")
    {
        return OpenGLType::Vec3;
    }
    else if (s_type == "vec4")
    {
        return OpenGLType::Vec4;
    }
    else
    {
        spdlog::error("[GLType::FromString] Unknown type : {}", s_type);
    }
}