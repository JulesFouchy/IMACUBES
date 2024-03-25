#pragma once

#include "CursorPositioner.hpp"

class CursorPositioner_AtAFixedDistance : public CursorPositioner {
public:
    CursorPositioner_AtAFixedDistance(Cursor* cursor);
    ~CursorPositioner_AtAFixedDistance() = default;

    void computePosition() override;

    void onWheelScroll(float dl) override;

private:
    float m_distance;
};