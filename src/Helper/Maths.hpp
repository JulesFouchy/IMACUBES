#pragma once

namespace MyMaths {
	const float TAU = 6.283185307179586476925286766559f;

	float Cos(float x);
	float Sin(float x);
	float Pow(float x, float p);
	float Abs(float x);
	float Sign(float x);
	float Log(float x, float base);
	int LogInt(int x, int base);
	
	float Lerp(float a, float b, float t);
}