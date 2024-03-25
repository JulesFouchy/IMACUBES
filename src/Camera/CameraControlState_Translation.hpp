#pragma once

#include "Camera.hpp"
#include "CameraControlState.hpp"
#include "glm/glm.hpp"

class CameraControlState_Translation : public CameraControlState {
public:
    CameraControlState_Translation(Camera* camera);
    ~CameraControlState_Translation() = default;

    void update() override;

    void onWheelUp() override;

private:
    glm::vec3 m_initialLookedAtPoint;
};