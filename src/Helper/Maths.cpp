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

float MyMaths::Lerp(float a, float b, float t) {
	return a + t * (b - a);
}