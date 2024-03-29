#include "Tool_RBF_HeightMap.hpp"
#include "RBF/RBF.hpp"

Tool_RBF_HeightMap::Tool_RBF_HeightMap()
{
    m_bSurfaceMode       = false;
    m_modulingFunction   = &m_inverse;
    m_modulingFunctionID = 1;
}

void Tool_RBF_HeightMap::addAnchorPoint(const glm::ivec3& pos)
{
    m_anchorPts.push_back(glm::ivec2(pos.x, pos.z));
    m_valuesAtAnchorPts.conservativeResize(m_valuesAtAnchorPts.size() + 1);
    m_valuesAtAnchorPts(m_valuesAtAnchorPts.size() - 1) = pos.y;
}

void Tool_RBF_HeightMap::evaluateRBFOnWorld(std::function<void(const glm::ivec3& pos)> whatToDoWithPos)
{
    RBF<glm::ivec2> rbf = RBF<glm::ivec2>(m_anchorPts, m_valuesAtAnchorPts, *m_modulingFunction);
    BoundingBox     worldBB;
    for (const glm::ivec3& pos : worldBB)
    {
        float d = rbf.eval(glm::vec2(pos.x, pos.z));
        if ((!m_bInvertSelection && condition(d, pos)) || (m_bInvertSelection && !condition(d, pos)))
        {
            whatToDoWithPos(pos);
        }
    }
}

bool Tool_RBF_HeightMap::condition(float h, const glm::ivec3& pos)
{
    if (m_bSurfaceMode)
        return abs(h - pos.y) < m_threshhold;
    else
        return pos.y < h + m_threshhold;
}

void Tool_RBF_HeightMap::reset()
{
    Tool_RBF::reset();
    m_anchorPts.clear();
}

void Tool_RBF_HeightMap::ImGui_Window()
{
    ImGui::Begin("RBF height map");
    bool bComputePreview = false;

    bComputePreview |= ImGui_ModulingFunction();
    ImGui::Separator();

    bComputePreview |= ImGui_Condition();
    ImGui::Separator();

    ImGui::Text("Anchor points");
    for (size_t k = 0; k < m_anchorPts.size(); ++k)
    {
        glm::ivec2& anchorPt = m_anchorPts[k];
        float&      value    = m_valuesAtAnchorPts[k];
        ImGui::PushID(k);
        bComputePreview |= ImGui::DragInt2("Pos", &anchorPt.x);
        bComputePreview |= ImGui::DragFloat("Val", &value);
        ImGui::PopID();
        ImGui::Separator();
    }

    ImGui_Finalize(bComputePreview);

    ImGui::End();
}