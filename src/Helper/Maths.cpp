#include "Maths.hpp"

#include <cmath>

float MyMaths::Cos(float x) {
	return std::cos(x);
}

float MyMaths::Sin(float x) {
	return std::sin(x);
}

float MyMaths::Pow(float x, float p) {
	return std::pow(x, p);
}

float MyMaths::Abs(float x) {
	return std::abs(x);
}

float MyMaths::Sign(float x) {
	return x == 0.0f ? 0.0f : MyMaths::Abs(x) / x;
}

float MyMaths::Log(float x, float base) {
	return log(x) / log(base);
}

int MyMaths::LogInt(int x, int base) {
	return round(Log(x, base));
}


int MyMaths::Ceil(float x) {
	return ceil(x);
}

int MyMaths::Clamp(int x, int a, int b) {
	if (x < a)
		return a;
	else if (x > b)
		return b;
	return x;
}


float MyMaths::Lerp(float a, float b, float t) {
	return a + t * (b - a);
}

float MyMaths::NormalizedDistance2D(const glm::ivec3& v0, const glm::ivec3& v1, const glm::ivec3& size, int c0, int c1) {
	glm::vec2 a0 = glm::vec2(v0[c0], v0[c1]);
	glm::vec2 a1 = glm::vec2(v1[c0], v1[c1]);
	glm::vec2 size2D = glm::vec2(size[c0], size[c1]);
	return glm::length((a0 - a1) / size2D);
}