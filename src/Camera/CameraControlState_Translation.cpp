#include "CameraControlState_Translation.hpp"
#include "CameraControlState_Rest.hpp"
#include "Debugging/Log.hpp"
#include "Helper/Maths.hpp"
#include "UI/Settings.hpp"

CameraControlState_Translation::CameraControlState_Translation(Camera* camera)
    : CameraControlState(camera), m_initialLookedAtPoint(camera->getLookedAtPoint())
{
}

void CameraControlState_Translation::update()
{
    glm::vec2 mouseDL = m_mouseInitialPosInInches - Input::MousePositionInInches();
    m_camera->setLookedAtPoint(m_initialLookedAtPoint + (m_camera->getLocalX() * mouseDL.x + m_camera->getLocalY() * mouseDL.y) * Settings::CAMERA_TRANSLATION_SPEED_PER_INCH * m_camera->m_sphereCoord.getRadius());

    m_camera->mustRecomputeTransformMatrix();
}

void CameraControlState_Translation::onWheelUp()
{
    m_camera->setControlState<CameraControlState_Rest>();
}