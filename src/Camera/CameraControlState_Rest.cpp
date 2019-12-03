#include "CameraControlState_Rest.hpp"
#include "CameraControlState_Rotation.hpp"

#include "Debugging/Log.hpp"

CameraControlState_Rest::CameraControlState_Rest(Camera* camera)
	: CameraControlState(camera)
{
	spdlog::warn("rest");
}

void CameraControlState_Rest::onWheelDown() {
	m_camera->setControlState<CameraControlState_Rotation>();
}