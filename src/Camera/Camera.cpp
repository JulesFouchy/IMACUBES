#include "Camera.hpp"
#include "CameraControlState_Rest.hpp"

#include "glm/gtc/matrix_transform.hpp"

#include "Helper/Maths.hpp"

#include "Debugging/Log.hpp"

Camera::Camera(const glm::vec3& lookedAtPoint)
	: m_projectionMatrix(1.0f), m_transformMatrix(1.0f), m_inverseTransformMatrix(1.0f), m_sphereCoord(5.0f, 1.8f, 0.0f), m_lookedAtPoint(lookedAtPoint),
	  m_bMustRecomputeProjectionMatrix(true), m_bMustRecomputeTransformMatrix(true),
	  m_controlState(std::make_unique<CameraControlState_Rest>(this))
{
}

void Camera::computeTransformMatrixAndItsInverse() {
	using namespace MyMaths;
	m_inverseTransformMatrix = glm::lookAt(m_sphereCoord.getXYZ() + m_lookedAtPoint, m_lookedAtPoint, glm::vec3(0.0f, Sign(Cos(m_sphereCoord.getAngleUp())), 0.0f));
	m_transformMatrix = glm::inverse(m_inverseTransformMatrix);

	m_bMustRecomputeTransformMatrix = false;
}

void Camera::computeProjectionMatrix() {
	m_projectionMatrix = glm::infinitePerspective(1.0f, Display::GetRatio(), 0.1f);

	m_bMustRecomputeProjectionMatrix = false;
}

Ray Camera::getRayGoingThroughMousePos() {
	glm::vec3 pos = getPosition();
	glm::vec3 mousePos = glm::unProject(glm::vec3(Input::MousePositionInPixels(), 0.0f), getViewMatrix(), getProjMatrix(), glm::vec4(0.0f, 0.0f, Display::GetWidth(), Display::GetHeight()));
	glm::vec3 dir = glm::normalize(mousePos - pos);
	return Ray(pos, dir);
}