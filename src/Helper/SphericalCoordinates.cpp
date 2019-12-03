#include "SphericalCoordinates.hpp"

#include "Maths.hpp"

#include "Debugging/Log.hpp"

void SphericalCoordinates::computeXYZ() {
	m_x = getRadius() * MyMaths::cos(getAngleUp()) * MyMaths::cos(-getAngleGround());
	m_y = getRadius() * MyMaths::sin(getAngleUp());
	m_z = getRadius() * MyMaths::cos(getAngleUp()) * MyMaths::sin(-getAngleGround());
	m_bMustRecomputeXYZ = false;
}