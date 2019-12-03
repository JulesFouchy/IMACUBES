#include "Camera.hpp"
#include "CameraControlState_Rest.hpp"

Camera::Camera()
	: m_viewMatrix(1.0f), m_sphereCoord(5.0f), m_controlState(new CameraControlState_Rest(this))
{

}