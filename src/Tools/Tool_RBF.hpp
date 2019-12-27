#pragma once
#include "Tool_RBF_Window.hpp"
#include <vector>
#include <glm/glm.hpp>
#include <Eigen/Dense>
#include "openGL/CubesGroup_WithoutMaterialIndices.hpp"
#include "Cursor/Cursor.hpp"

class Tool_RBF {
friend class PopupWindow_RBF;
public:
	Tool_RBF();
	~Tool_RBF()=default;
	void onLeftClick(const Cursor& cursor);

	void showGUI();

private: 
	void addCubeToSelection(const glm::vec3&, const double valueAtAnchorPoint);

	PopupWindow_RBF m_window;
	std::vector<glm::vec3> m_anchorPts;
	Eigen::VectorXd m_valuesAtAnchorPts;
	CubesGroup_WithoutMaterialIndices m_group;
};