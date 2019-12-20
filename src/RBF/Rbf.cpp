#include "Rbf.hpp"

#include "Eigen/Dense"
#include <math.h>
#include <imgui.h>
#include <glm/glm.hpp>

double distance(glm::vec3 a, b) {
	return glm::distance(a, b);
}

double multiQuadra(glm::vec3 a,b){
	return sqrt(1 + sqrt(pow(glm::distance(a,b),2));
}

double invMultiQuadra(glm::vec3 a, b){
	return  1 / pow(glm::distance(a,b),2) ;
}

double gaussian(glm::vec3 a, b){
	return exp(-pow(glm::distance(a,b),2));

}
	
Eigen::VectorXd calculOmega(const std::vector<glm::vec3> &anchorPts,const Eigen::VectorXd &valuesAtAnchorPts) {
	Eigen::MatrixXd anchorMatrix(anchorPts.size(), anchorPts.size());

	for (int i = 0, i < anchorPts.size(), ++i) {
		for (int j = 0, j < anchorPts.size(), ++j) {
			anchorMatrix[i, j] = gaussian(anchorPts[i], anchorPts[j]);
		}
	}

	return anchorMatrix.inverse()* valuesAtAnchorPts;
}