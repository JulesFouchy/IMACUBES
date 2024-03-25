#include "CameraControlState_Rest.hpp"
#include "CameraControlState_Rotation.hpp"
#include "CameraControlState_Translation.hpp"
#include "Debugging/Log.hpp"
#include "Helper/Maths.hpp"
#include "UI/Input.hpp"
#include "UI/Settings.hpp"

CameraControlState_Rest::CameraControlState_Rest(Camera* camera)
    : CameraControlState(camera)
{
}

void CameraControlState_Rest::onWheelDown()
{
    if (Input::KeyIsDown(SHIFT))
    {
        m_camera->setControlState<CameraControlState_Translation>();
    }
    else
    {
        m_camera->setControlState<CameraControlState_Rotation>();
    }
}

void CameraControlState_Rest::onWheelScroll(float dl)
{
    m_camera->m_sphereCoord.radius() *= MyMaths::Pow(Settings::CAMERA_SCALE_RADIUS_PER_SCROLL, dl);

    m_camera->m_bMustRecomputeTransformMatrix = true;
}