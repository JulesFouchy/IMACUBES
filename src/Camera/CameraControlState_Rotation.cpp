#include "CameraControlState_Rotation.hpp"
#include "CameraControlState_Rest.hpp"

#include "UI/Settings.hpp"

#include "Helper/Maths.hpp"

#include "Debugging/Log.hpp"

CameraControlState_Rotation::CameraControlState_Rotation(Camera* camera)
	: CameraControlState(camera),
	m_initialRadius(camera->m_sphereCoord.getRadius()),
	m_initialAngleGround(camera->m_sphereCoord.getAngleGround()),
	m_initialAngleUp(camera->m_sphereCoord.getAngleUp())
{
}

void CameraControlState_Rotation::update(float dt) {
	glm::vec2 mouseDL = Input::MousePositionInInches() - m_mouseInitialPosInInches;
	mouseDL.x *= MyMaths::Cos(m_camera->m_sphereCoord.getAngleUp());
	m_camera->m_sphereCoord.angleGround() = m_initialAngleGround + mouseDL.x * Settings::CAMERA_ROTATION_SPEED_IN_TURNS_PER_INCH * MyMaths::TAU;
	m_camera->m_sphereCoord.angleUp()     = m_initialAngleUp     + mouseDL.y * Settings::CAMERA_ROTATION_SPEED_IN_TURNS_PER_INCH * MyMaths::TAU;

	m_camera->m_bMustRecomputeTransformMatrix = true;
}

void CameraControlState_Rotation::onWheelUp() {
	m_camera->setControlState<CameraControlState_Rest>();
}