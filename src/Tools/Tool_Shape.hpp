#pragma once

#include <functional>
#include "CubesMap/BoundingBox.hpp"
#include "Tool.hpp"

class Tool_Shape : public Tool {
public:
    Tool_Shape()          = default;
    virtual ~Tool_Shape() = default;

    void onLeftClicDown(const Cursor& cursor) override;
    void onRightClicDown(const Cursor& cursor) override;

protected:
    virtual void applyOnShape(std::function<void(const glm::ivec3& pos)> whatToDoWithPos) = 0;

    void addCubes();
    void removeCubes();
    void replaceMaterials();
    void computePreview();

protected:
    BoundingBox m_bbox;
};