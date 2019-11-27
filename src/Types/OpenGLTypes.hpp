#pragma once

#include <string>

enum OpenGLType {
	Int,
	Float,
	Vec2,
	Vec3,
	Vec4,
};

namespace GLType {
	OpenGLType FromString(const std::string& s_type);
}