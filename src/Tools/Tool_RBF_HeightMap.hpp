#pragma once

#include "Tool_RBF.hpp"

class Tool_RBF_HeightMap : public Tool_RBF {
public:
    Tool_RBF_HeightMap();
    ~Tool_RBF_HeightMap() = default;

private:
    void reset() override;

    void addAnchorPoint(const glm::ivec3& pos) override;
    void evaluateRBFOnWorld(std::function<void(const glm::ivec3& pos)> whatToDoWithPos) override;
    void ImGui_Window() override;

    bool condition(float h, const glm::ivec3& pos);

private:
    std::vector<glm::ivec2> m_anchorPts;
};