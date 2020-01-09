#pragma once

#include "Function.hpp"

#include <glm/glm.hpp>
#include <Eigen/Dense>

#include <vector>

template <typename T> // vector of any dimension (mainly 2 or 3)
class RBF{
public:
	RBF(const std::vector<T>& anchorPts, const Eigen::VectorXf& valuesAtAnchorPts, const Function& modulingFunction)
		: m_anchorPts(anchorPts), m_modulingFunction(modulingFunction)
	{
		computeOmegas(valuesAtAnchorPts);
	}

	float eval(const T& pos) {
		float sum = 0.0;
		for (int i = 0; i < m_anchorPts.size(); ++i) {
			sum += m_omegas[i] * m_modulingFunction.eval(glm::distance(m_anchorPts[i], pos));
		}
		return sum;
	}

private:
	void computeOmegas(const Eigen::VectorXf& valuesAtAnchorPts) {
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

private:
	std::vector<T> m_anchorPts;
	Eigen::VectorXf m_omegas;
	const Function& m_modulingFunction;
};