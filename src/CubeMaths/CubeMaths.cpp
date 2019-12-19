#include "CubeMaths.hpp"

#include <limits>

glm::ivec3 CubeMaths::CubeContaining(glm::vec3 pos) {
	return glm::ivec3(round(pos.x), round(pos.y), round(pos.z));
}

float CubeMaths::IntersectionRayCube_WROIC(Ray ray, glm::vec3 cubePos) { // Ray Origin must be inside the cube !!!
	float actualT = std::numeric_limits<float>::infinity();
	for (int coord = 0; coord < 3; ++coord) {
		for (int sign = -1; sign < 2; sign+=2) {
			float t = IntersectionRayPlane(ray, coord, cubePos[coord] + sign * 0.5f);
			if (t > 0.0f && t < actualT)
				actualT = t;
		}
	}
	return actualT;
}

float CubeMaths::IntersectionRayPlane(Ray ray, int coord, float coordValue) { // dir must be normalized !!!
	return (coordValue - ray.origin[coord]) / ray.direction[coord];
}

