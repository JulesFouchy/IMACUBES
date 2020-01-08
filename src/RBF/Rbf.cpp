#include "RBF.hpp"


RBF::RBF(const std::vector<glm::vec3>& anchorPts, const Eigen::VectorXf& valuesAtAnchorPts, const Function& modulingFunction)
	: m_anchorPts(anchorPts), m_modulingFunction(modulingFunction)
{
	computeOmegas(valuesAtAnchorPts);
}

float multiQuadra(float x){
	return sqrt(1 + sqrt(pow(x,2)));
}

float invMultiQuadra(float x){
	return  1 / pow(x,2) ;
}

float gaussian(float x, float growthSpeed){
	return exp(-pow(x * growthSpeed,2));
}

void RBF::computeOmegas(const Eigen::VectorXf& valuesAtAnchorPts) {
	if (m_anchorPts.size() > 0) {
		Eigen::MatrixXf anchorMatrix(m_anchorPts.size(), m_anchorPts.size());

		for (int i = 0; i < m_anchorPts.size(); ++i) {
			for (int j = 0; j < m_anchorPts.size(); ++j) {
				anchorMatrix(i, j) = m_modulingFunction.eval(glm::distance(m_anchorPts[i], m_anchorPts[j]));
			}
		}

		m_omegas = anchorMatrix.householderQr().solve(valuesAtAnchorPts);
	}
}

float RBF::eval(const glm::vec3& pos){
	float sum = 0.0;
	for (int i = 0; i < m_anchorPts.size(); ++i) {
		sum += m_omegas[i] * m_modulingFunction.eval(glm::distance(m_anchorPts[i], pos));
	}
	return sum;
}