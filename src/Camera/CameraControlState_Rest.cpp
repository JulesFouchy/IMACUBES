#include "CameraControlState_Rest.hpp"
#include "CameraControlState_Rotation.hpp"

#include "Debugging/Log.hpp"

#include "UI/Settings.hpp"

#include "Helper/Maths.hpp"

CameraControlState_Rest::CameraControlState_Rest(Camera* camera)
	: CameraControlState(camera)
{
}

void CameraControlState_Rest::onWheelDown() {
	m_camera->setControlState<CameraControlState_Rotation>();
}

void CameraControlState_Rest::onWheelScroll(float dl){
	m_camera->m_sphereCoord.radius() *= MyMaths::Pow(Settings::CAMERA_SCALE_RADIUS_PER_SCROLL, dl);

	m_camera->m_bMustRecomputeTransformMatrix = true;
}