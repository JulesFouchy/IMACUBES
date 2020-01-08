#pragma once

#include <glm/glm.hpp>
#include <Eigen/Dense>

#include <functional>
#include <vector>

#include "Debugging/Log.hpp"

float multiQuadra(float x);
float invMultiQuadra(float x);
float gaussian(float x, float growthSpeed);

class RBF{
public:
	RBF(const std::vector<glm::vec3>& anchorPts, const Eigen::VectorXf& valuesAtAnchorPts, const std::function<float(float)>& phi);

	float eval(const glm::vec3& pos);

private:
	void computeOmegas(const Eigen::VectorXf& valuesAtAnchorPts);

private:
	std::vector<glm::vec3> m_anchorPts;
	Eigen::VectorXf m_omegas;
	std::function<float(float)> m_phi;
};