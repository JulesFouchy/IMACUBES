#include "Camera.hpp"
#include "CameraControlState_Rest.hpp"

#include "glm/gtc/matrix_transform.hpp"

#include "Locator/Locate.hpp"
#include "Renderer/Renderer.hpp"

#include "Helper/Maths.hpp"

#include "Debugging/Log.hpp"

#include <imgui/imgui.h>

Camera::Camera(const glm::vec3& lookedAtPoint)
	: m_projectionMatrix(1.0f), m_fieldOfViewInRadians(Settings::CAMERA_FIELD_OF_VIEW), m_bMustRecomputeProjectionMatrix(true),
	  m_transformMatrix(1.0f), m_inverseTransformMatrix(1.0f), m_sphereCoord(34.0f, 0.0f, 0.28f), m_lookedAtPoint(lookedAtPoint), m_bMustRecomputeTransformMatrix(true)
{
}

void Camera::initAfterApp() {
	m_controlState = std::make_unique<CameraControlState_Rest>(this);
}

void Camera::computeTransformMatrixAndItsInverse() {
	using namespace MyMaths;
	m_inverseTransformMatrix = glm::lookAt(m_sphereCoord.getXYZ() + m_lookedAtPoint, m_lookedAtPoint, glm::vec3(0.0f, Sign(Cos(m_sphereCoord.getAngleUp())), 0.0f));
	m_transformMatrix = glm::inverse(m_inverseTransformMatrix);

	m_bMustRecomputeTransformMatrix = false;
}

void Camera::computeProjectionMatrix() {
	m_projectionMatrix = glm::infinitePerspective(m_fieldOfViewInRadians, Locate::renderer().getRatio(), 0.1f);

	m_bMustRecomputeProjectionMatrix = false;
}

Ray Camera::getRayGoingThroughMousePos() {
	glm::vec3 pos = getPosition();
	glm::vec3 mousePos = glm::unProject(glm::vec3(Input::MousePositionInPixels(), 0.0f), getViewMatrix(), getProjMatrix(), glm::vec4(0.0f, 0.0f, Locate::renderer().getWidth(), Locate::renderer().getHeight()));
	glm::vec3 dir = glm::normalize(mousePos - pos);
	return Ray(pos, dir);
}

void Camera::resetTransform() {
	m_sphereCoord = SphericalCoordinates(34.0f, 0.0f, 0.28f);
	m_lookedAtPoint = glm::vec3(0.0f);
	m_bMustRecomputeTransformMatrix = true;
}

bool Camera::ImGui_View() {
	if (ImGui::SliderFloat("Field of view", &m_fieldOfViewInRadians, 0.01, 3.14)) {
		mustRecomputeProjectionMatrix();
		return true;
	}
	return false;
}

bool Camera::ImGui_Transform() {
	bool modifs = m_sphereCoord._ImGui_CoordinatesSliders();
	modifs |=     ImGui::DragFloat3("Looking at", (float*)&m_lookedAtPoint);
	if (modifs)
		m_bMustRecomputeTransformMatrix = true;
	return modifs;
}