#pragma once
#include "Tool_RBF_Window.hpp"
#include <vector>
#include <glm/glm.hpp>
#include <Eigen/Dense>
#include "openGL/CubesGroup_WithoutMaterialIndices.hpp"
#include "Cursor/Cursor.hpp"
#include "Tool_Shape.hpp"

class Tool_RBF :public Tool_Shape{
friend class PopupWindow_RBF;
public:
	Tool_RBF();
	~Tool_RBF()=default;
	void onLeftClicDown(const Cursor& cursor) override;
	void update(const Cursor& cursor) override;
	

private: 
	void addCubeToSelection(const glm::vec3&, const double valueAtAnchorPoint);
	void applyOnShape(std::function<void(const glm::ivec3 & pos)> whatToDoWithPos) override;
	void showGUI();
	PopupWindow_RBF m_window;
	std::vector<glm::vec3> m_anchorPts;
	Eigen::VectorXd m_valuesAtAnchorPts;
	int m_selectedPhi;
	float vitesse_decroissance;
};

