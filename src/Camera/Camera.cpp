#include "Camera.hpp"
#include "CameraControlState_Rest.hpp"

Camera::Camera()
	: m_viewMatrix(1.0f), m_sphereCoord(5.0f), m_controlState(std::make_unique<CameraControlState_Rest>(this))
{

}