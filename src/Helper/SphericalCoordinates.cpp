#include "SphericalCoordinates.hpp"

#include <cstdlib>

void SphericalCoordinates::computeXYZ() {
	m_x = getRadius() * cos(getAngleUp()) * cos(-getAngleGround());
	m_y = getRadius() * sin(getAngleUp());
	m_z = getRadius() * cos(getAngleUp()) * sin(-getAngleGround());
	m_bMustRecomputeXYZ = false;
}