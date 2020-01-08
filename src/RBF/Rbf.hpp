#pragma once

#include <glm/glm.hpp>
#include <Eigen/Dense>
#include <functional>
#include "Debugging/Log.hpp"
#include <vector>

double distance(glm::vec3 a, glm::vec3 b);
double multiQuadra(double x);
double invMultiQuadra(double x);
double gaussian(double x);



class RBF{
public:
	RBF(std::vector<glm::vec3> anchorPts, Eigen::VectorXd valuesAtAnchorPts, std::function<double(double)> phi);

	double eval(const glm::vec3& pos);


private:
	void calculOmega(Eigen::VectorXd valuesAtAnchorPts);
	std::vector <glm::vec3> m_anchorPts;
	Eigen::VectorXd m_omega;
	std::function<double(double)> m_phi;
};