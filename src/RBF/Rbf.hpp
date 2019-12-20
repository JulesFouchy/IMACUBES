#pragma once
#include <glm>
#include "glm/glm.hpp"

#include "Debugging/Log.hpp"

double distance(glm::vec3 a, b);
double multiQuadra(glm::vec3 a, b);
double invMultiQuadra(glm::vec3 a, b);
double gaussian(glm::vec3 a, b);
Eigen::VectorXd calculOmega(const std::vector<glm::vec3>& anchorPts, const Eigen::VectorXd& valuesAtAnchorPts);

