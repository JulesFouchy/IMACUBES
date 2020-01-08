#pragma once

#include <glm/glm.hpp>
#include <Eigen/Dense>
#include <functional>
#include "Debugging/Log.hpp"
#include <vector>

float distance(glm::vec3 a, glm::vec3 b);
float multiQuadra(float x);
float invMultiQuadra(float x);
float gaussian(float x, float growthSpeed);



class RBF{
public:
	RBF(std::vector<glm::vec3> anchorPts, Eigen::VectorXf valuesAtAnchorPts, std::function<double(double)> phi);

	float eval(const glm::vec3& pos);


private:
	void calculOmega(Eigen::VectorXf valuesAtAnchorPts);
	std::vector <glm::vec3> m_anchorPts;
	Eigen::VectorXf m_omega;
	std::function<double(double)> m_phi;
};