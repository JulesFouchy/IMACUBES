#include "CameraControlState_Rest.hpp"
#include "CameraControlState_Rotation.hpp"

CameraControlState_Rest::CameraControlState_Rest(Camera* camera)
	: CameraControlState(camera)
{}

void CameraControlState_Rest::onWheelDown() {
	m_camera->setControlState<CameraControlState_Rotation>();
}