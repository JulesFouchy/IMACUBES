#pragma once

#include "Tool_RBF.hpp"

class Tool_RBF_DistanceField : public Tool_RBF {
public:
	Tool_RBF_DistanceField();
	~Tool_RBF_DistanceField() = default;

private:
	void reset() override;

	void addAnchorPoint(const glm::ivec3& pos) override;
	void evaluateRBFOnWorld(std::function<void(const glm::ivec3 & pos)> whatToDoWithPos) override;
	void ImGui_Window() override;

	bool condition(float d);

private:
	std::vector<glm::ivec3> m_anchorPts;
};