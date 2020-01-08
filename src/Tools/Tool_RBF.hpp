#pragma once

#include "Tool_Shape.hpp"

#include <glm/glm.hpp>
#include <Eigen/Dense>

#include <vector>

class Tool_RBF : public Tool_Shape {
public:
	Tool_RBF();
	~Tool_RBF() = default;

	void onLeftClicDown(const Cursor& cursor) override;
	void update(const Cursor& cursor) override;

private:
	void applyOnShape(std::function<void(const glm::ivec3& pos)> whatToDoWithPos) override;

	void addCubeToSelection(const glm::vec3& pos, double value);

	void reset();

	void ImGui_Window();

private:
	std::vector<glm::vec3> m_anchorPts;
	Eigen::VectorXf m_valuesAtAnchorPts;

	int m_selectedPhiID;
	float vitesse_decroissance;
};

