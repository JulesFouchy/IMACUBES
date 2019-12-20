#include "Camera.hpp"
#include "CameraControlState_Rest.hpp"

#include "glm/gtc/matrix_transform.hpp"

#include "Helper/Maths.hpp"

#include "Debugging/Log.hpp"

Camera::Camera()
	: m_transformMatrix(1.0f), m_inverseTransformMatrix(1.0f), m_sphereCoord(5.0f, 1.8f, 0.0f), m_translation(0.0f),
	  m_bMustRecomputeTransformMatrix(true),
	  m_controlState(std::make_unique<CameraControlState_Rest>(this))
{
}

void Camera::computeTransformMatrixAndItsInverse() {
	using namespace MyMaths;
	m_transformMatrix = glm::inverse(glm::lookAt(m_sphereCoord.getXYZ() + glm::vec3(50.0f), glm::vec3(50.0f), glm::vec3(0.0f, Sign(Cos(m_sphereCoord.getAngleUp())), 0.0f)));
	m_inverseTransformMatrix = glm::inverse(m_transformMatrix);


	m_bMustRecomputeTransformMatrix = false;
}

Ray Camera::getRayGoingThroughMousePos() {
	glm::vec3 pos = getPosition();
	glm::vec3 mousePos = glm::unProject(glm::vec3(Input::MousePositionInPixels(), 0.0f), getViewMatrix(), getProjMatrix(), glm::vec4(0.0f, 0.0f, Display::GetWidth(), Display::GetHeight()));
	glm::vec3 dir = glm::normalize(mousePos - pos);
	return Ray(pos, dir);
}