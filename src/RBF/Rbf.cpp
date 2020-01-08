#include "Rbf.hpp"
#include <math.h>
#include <imgui.h>


RBF::RBF(std::vector<glm::vec3> anchorPts, Eigen::VectorXd valuesAtAnchorPts, std::function<double(double)> phi)
	: m_anchorPts(anchorPts), m_phi(phi)
{
	calculOmega(valuesAtAnchorPts);
}

double distance(glm::vec3 a, glm::vec3 b) {
	return glm::distance(a, b);
}

double multiQuadra(double x){
	return sqrt(1 + sqrt(pow(x,2)));
}

double invMultiQuadra(double x){
	return  1 / pow(x,2) ;
}

double gaussian(double x){
	double vitesse_decroissance = 1.0;
	return exp(-pow(x/vitesse_decroissance,2));

}


void RBF::calculOmega(Eigen::VectorXd valuesAtAnchorPts) {
	if (m_anchorPts.size() > 0) {
		Eigen::MatrixXd anchorMatrix(m_anchorPts.size(), m_anchorPts.size());

		for (int i = 0; i < m_anchorPts.size(); ++i) {
			for (int j = 0; j < m_anchorPts.size(); ++j) {
				anchorMatrix(i, j) = m_phi(glm::distance(m_anchorPts[i], m_anchorPts[j]));
			}
		}

		m_omega = anchorMatrix.inverse() * valuesAtAnchorPts;
	}
}

double RBF::eval(const glm::vec3& pos){
	double somme = 0.0;
	for (int i = 0; i < m_anchorPts.size(); ++i) {
		somme = somme + m_omega[i]* m_phi(glm::distance(m_anchorPts[i], pos));
	}

	return somme;

}