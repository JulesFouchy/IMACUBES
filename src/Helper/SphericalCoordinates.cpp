#include "SphericalCoordinates.hpp"

#include "Maths.hpp"

#include "Debugging/Log.hpp"

void SphericalCoordinates::computeXYZ() {
	using namespace MyMaths;
	m_x = getRadius() * Cos(getAngleUp()) * Cos(-getAngleGround());
	m_y = getRadius() * Sin(getAngleUp());
	m_z = getRadius() * Cos(getAngleUp()) * Sin(-getAngleGround());
	m_bMustRecomputeXYZ = false;
}