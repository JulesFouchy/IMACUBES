#pragma once

struct SphericalCoordinates {
	SphericalCoordinates(float radius = 1.0f, float angleGround = 0.0f, float angleUp = 0.0f)
		: m_radius(radius), m_angleGround(angleGround), m_angleUp(angleUp),
		  m_x(0.0f), m_y(0.0f), m_z(0.0f),
		  m_bMustRecomputeXYZ(true)
	{}

	inline float& radius() { m_bMustRecomputeXYZ = true;  return m_radius; }
	inline float& angleGround() { m_bMustRecomputeXYZ = true;  return m_angleGround; }
	inline float& angleUp() { m_bMustRecomputeXYZ = true;  return m_angleUp; }

	inline const float getRadius() const { return m_radius; }
	inline const float getAngleGround() const { return m_angleGround; }
	inline const float getAngleUp() const { return m_angleUp; }

	inline const float getX() { if (m_bMustRecomputeXYZ) computeXYZ(); return m_x; }
	inline const float getY() { if (m_bMustRecomputeXYZ) computeXYZ(); return m_y; }
	inline const float getZ() { if (m_bMustRecomputeXYZ) computeXYZ(); return m_z; }

private:
	void computeXYZ();

private:
	float m_radius;
	float m_angleGround;
	float m_angleUp;

	float m_x;
	float m_y;
	float m_z;

	bool m_bMustRecomputeXYZ;
};