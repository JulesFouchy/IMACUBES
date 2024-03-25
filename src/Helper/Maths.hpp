#pragma once

#include <glm/glm.hpp>

namespace MyMaths {
const float TAU = 6.283185307179586476925286766559f;

float Cos(float x);
float Sin(float x);
float Pow(float x, float p);
float Abs(float x);
float Sign(float x);
float Log(float x, float base);
int   LogInt(int x, int base);

int Ceil(float x);
int Clamp(int x, int a, int b);

float Lerp(float a, float b, float t);

float NormalizedDistance2D(const glm::ivec3& v0, const glm::ivec3& v1, const glm::ivec3& size, int c0, int c1);

template<typename T>
float Distance(const T& v1, const T& v2);
} // namespace MyMaths