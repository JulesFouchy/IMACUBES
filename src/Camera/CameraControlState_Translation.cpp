#include "CameraControlState_Translation.hpp"
#include "CameraControlState_Rest.hpp"

#include "UI/Settings.hpp"

#include "Helper/Maths.hpp"

#include "Debugging/Log.hpp"

CameraControlState_Translation::CameraControlState_Translation(Camera* camera)
	: CameraControlState(camera),
	m_initialTranslation(camera->getTranslation())
{
}

void CameraControlState_Translation::update(float dt) {
	glm::vec2 mouseDL = m_mouseInitialPosInInches - Input::MousePositionInInches();
	m_camera->setTranslation(m_initialTranslation + (m_camera->getLocalX()*mouseDL.x +m_camera->getLocalY()*mouseDL.y)* Settings::CAMERA_TRANSLATION_SPEED_PER_INCH * m_camera->m_sphereCoord.getRadius());

	m_camera->m_bMustRecomputeTransformMatrix = true;
}

void CameraControlState_Translation::onWheelUp() {
	m_camera->setControlState<CameraControlState_Rest>();
}