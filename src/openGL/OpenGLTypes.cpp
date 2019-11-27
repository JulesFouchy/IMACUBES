#include "OpenGLTypes.hpp"

#include "Debugging/Log.hpp"


OpenGLType GLType::FromString(const std::string& s_type) {
	if (s_type == "int") {
		return Int;
	}
	else if (s_type == "float") {
		return Float;
	}
	else if (s_type == "vec2") {
		return Vec2;
	}
	else if (s_type == "vec3") {
		return Vec3;
	}
	else if (s_type == "vec4") {
		return Vec4;
	}
	else {
		spdlog::error("[GLType::FromString] Unknown type : {}", s_type);
	}
}