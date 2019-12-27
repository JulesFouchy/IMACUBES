#pragma once

#include <glm/glm.hpp>
#include <Eigen/Dense>

#include "Debugging/Log.hpp"

double distance(glm::vec3 a, glm::vec3 b);
double multiQuadra(glm::vec3 a, glm::vec3 b);
double invMultiQuadra(glm::vec3 a, glm::vec3 b);
double gaussian(glm::vec3 a, glm::vec3 b);
Eigen::VectorXd calculOmega(const std::vector<glm::vec3>& anchorPts, const Eigen::VectorXd& valuesAtAnchorPts);

class RBF{
public:
	RBF(std::vector<glm::vec3> anchorPts, Eigen::VectorXd valuesAtAnchorPts) {
		omega = calculOmega(anchorPts, valuesAtAnchorPts);
	}
private:
	std::vector <glm::vec3> anchorPts;
	Eigen::VectorXd omega;
};