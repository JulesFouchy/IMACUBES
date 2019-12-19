#pragma once

#include <glm/glm.hpp>

namespace CubeMaths {
	glm::ivec3 CubeContaining(glm::vec3 pos);

	float IntersectionRayCube_WROIC(glm::vec3 rayPos, glm::vec3 rayDir, glm::vec3 cubePos); // Ray Origin must be inside the cube !!!
	
	// Intersection with a plane vec3[coord] = coordValue (coord being either 0, 1 or 2 for x, y or z respectively)
	float IntersectionRayPlane(glm::vec3 pos, glm::vec3 dir, int coord, float coordValue); // dir must be normalized !!!
}