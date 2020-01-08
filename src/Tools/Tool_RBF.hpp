#pragma once

#include "Tool_RBF_Window.hpp"

#include <glm/glm.hpp>
#include <Eigen/Dense>

#include <vector>

#include "Tool_Shape.hpp"

class Tool_RBF : public Tool_Shape{
friend class PopupWindow_RBF;
public:
	Tool_RBF();
	~Tool_RBF() = default;

	void onLeftClicDown(const Cursor& cursor) override;
	void update(const Cursor& cursor) override;

private:
	void applyOnShape(std::function<void(const glm::ivec3& pos)> whatToDoWithPos) override;

	void addCubeToSelection(const glm::vec3& pos, double value);

private:
	std::vector<glm::vec3> m_anchorPts;
	Eigen::VectorXf m_valuesAtAnchorPts;

	int m_selectedPhi;
	float vitesse_decroissance;

	PopupWindow_RBF m_window;
};

