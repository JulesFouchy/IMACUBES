#pragma once

#include "Tool_Shape_Radial.hpp"

class Tool_Cube : public Tool_Shape_Radial {
public:
    Tool_Cube()  = default;
    ~Tool_Cube() = default;

private:
    void applyOnShape(std::function<void(const glm::ivec3& pos)> whatToDoWithPos) override;
};