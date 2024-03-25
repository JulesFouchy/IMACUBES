#pragma once

#include <glm/glm.hpp>
#include "Helper/Ray.hpp"

namespace CubeMaths {
glm::ivec3 CubeContaining(glm::vec3 pos);

float IntersectionRayCube_WROIC(Ray ray, glm::vec3 cubePos); // Ray Origin must be inside the cube !!!
float IntersectionRayWorldborder(Ray ray);

// Intersection with a plane vec3[coord] = coordValue (coord being either 0, 1 or 2 for x, y or z respectively)
float IntersectionRayPlane(Ray ray, int coord, float coordValue); // dir must be normalized !!!
} // namespace CubeMaths