#include "Camera.hpp"
#include "CameraControlState_Rest.hpp"

#include "glm/gtc/matrix_transform.hpp"

#include "UI/Settings.hpp"

#include "Helper/Maths.hpp"

#include "Debugging/Log.hpp"

Camera::Camera()
	: m_transformMatrix(1.0f), m_inverseTransformMatrix(1.0f), m_sphereCoord(5.0f, 1.8f, 0.0f),
	  m_bMustRecomputeTransformMatrix(true),
	  m_controlState(std::make_unique<CameraControlState_Rest>(this))
{
}

void Camera::onWheelScroll(float dl) {
	m_sphereCoord.radius() *= MyMaths::pow(Settings::CAMERA_SCALE_RADIUS_PER_SCROLL, dl);

	m_bMustRecomputeTransformMatrix = true;
}

void Camera::computeTransformMatrixAndItsInverse() {
	m_transformMatrix = glm::lookAt(m_sphereCoord.getXYZ(), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	m_inverseTransformMatrix = glm::inverse(m_transformMatrix);

	m_bMustRecomputeTransformMatrix = false;
}