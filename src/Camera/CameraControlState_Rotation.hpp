#pragma once

#include "Camera.hpp"
#include "CameraControlState.hpp"

class CameraControlState_Rotation : public CameraControlState {
public:
    CameraControlState_Rotation(Camera* camera);
    ~CameraControlState_Rotation() = default;

    void update() override;

    void onWheelUp() override;

private:
    float m_initialRadius;
    float m_initialAngleGround;
    float m_initialAngleUp;
};