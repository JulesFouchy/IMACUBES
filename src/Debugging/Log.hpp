#pragma once

#include "spdlog/spdlog.h"

#include "glm/glm.hpp"

class Log {
public:
	static void Initialize();

	static void separationLine();
	static void log(glm::vec2 v);
	static void log(glm::vec3 v);
	static void log(glm::vec4 v);
	static void log(glm::mat3x3 mat);
	static void log(glm::mat4x4 mat);
private:
	Log();
	~Log();
};