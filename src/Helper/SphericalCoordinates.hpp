#pragma once

struct SphericalCoordinates {
	SphericalCoordinates(float radius = 1.0f, float angleGround = 0.0f, float angleUp = 0.0f)
		: radius(radius), angleGround(angleGround), angleUp(angleUp)
	{}
	float radius;
	float angleGround;
	float angleUp;

	inline float x() { return 0.0f; }
	inline float y() { return 0.0f; }
	inline float z() { return 0.0f; }
};