#pragma once

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include "Helper/Display.hpp"
#include "Helper/SphericalCoordinates.hpp"
#include "Helper/Ray.hpp"

#include "UI/Settings.hpp"

#include "CameraControlState.hpp"

#include "Debugging/Log.hpp"

#include "imgui/imgui.h"

#include <memory>

class Camera {
friend class CameraControlState_Rest;
friend class CameraControlState_Rotation;
friend class CameraControlState_Translation; 
public:
	Camera(const glm::vec3& lookedAtPoint);
	~Camera() = default;

	inline const glm::mat4& getViewMatrix() { if(m_bMustRecomputeTransformMatrix) computeTransformMatrixAndItsInverse(); return m_inverseTransformMatrix; }
	inline const glm::mat4& getProjMatrix() { if(m_bMustRecomputeProjectionMatrix) computeProjectionMatrix(); return m_projectionMatrix; }
	
	inline void mustRecomputeProjectionMatrix() { m_bMustRecomputeProjectionMatrix = true; }

	inline void update(float dt) { m_controlState->update(dt); }

	inline void onWheelDown() { m_controlState->onWheelDown(); }
	inline void onWheelUp()   { m_controlState->onWheelUp();   }
	inline void onWheelScroll(float dl) { m_controlState->onWheelScroll(dl); }

	inline glm::vec3 getLocalX() { return glm::normalize( getTransformMatrix() * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f) ); }
	inline glm::vec3 getLocalY() { return glm::normalize( getTransformMatrix() * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f) ); }
	inline glm::vec3 getLocalZ() { return glm::normalize( getTransformMatrix() * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f) ); }
	inline glm::vec3 getPosition() { return getTransformMatrix() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f); }

	Ray getRayGoingThroughMousePos();

	inline const glm::vec3& getLookedAtPoint() const { return m_lookedAtPoint; }
	inline void setLookedAtPoint(const glm::vec3& newLookedAtPoint) { m_lookedAtPoint = newLookedAtPoint; m_bMustRecomputeTransformMatrix = true; }

	inline void resetFieldOfView() { m_fieldOfViewInRadians = Settings::DEFAULT_CAMERA_FIELD_OF_VIEW; mustRecomputeProjectionMatrix(); }
	bool ImGui_Sliders();

private:
	inline const glm::mat4& getTransformMatrix() { if (m_bMustRecomputeTransformMatrix) computeTransformMatrixAndItsInverse(); return m_transformMatrix; }

	void computeTransformMatrixAndItsInverse();
	void computeProjectionMatrix();

	template <typename T>
	inline void setControlState() {
		m_controlState = std::make_unique<T>(this);
	}

private:
	glm::mat4 m_projectionMatrix;
	float m_fieldOfViewInRadians;
	bool m_bMustRecomputeProjectionMatrix;

	glm::mat4 m_transformMatrix;
	glm::mat4 m_inverseTransformMatrix;
	SphericalCoordinates m_sphereCoord;
	glm::vec3 m_lookedAtPoint;
	bool m_bMustRecomputeTransformMatrix;

	std::unique_ptr<CameraControlState> m_controlState;
};