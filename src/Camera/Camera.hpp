#pragma once

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include "Helper/Display.hpp"
#include "Helper/SphericalCoordinates.hpp"
#include "Helper/Ray.hpp"

#include "CameraControlState.hpp"

#include "Debugging/Log.hpp"

#include "imgui/imgui.h"

#include <memory>

class Camera {
friend class CameraControlState_Rest;
friend class CameraControlState_Rotation;
friend class CameraControlState_Translation; 
public:
	Camera();
	~Camera() = default;

	inline const glm::mat4& getViewMatrix() { if(m_bMustRecomputeTransformMatrix) computeTransformMatrixAndItsInverse(); return m_inverseTransformMatrix; }
	inline const glm::mat4 getProjMatrix() { return glm::infinitePerspective(1.0f, Display::GetRatio(), 0.1f);  } // TODO return a reference to a member

	inline void update(float dt) { m_controlState->update(dt); }

	inline void onWheelDown() { m_controlState->onWheelDown(); }
	inline void onWheelUp()   { m_controlState->onWheelUp();   }
	inline void onWheelScroll(float dl) { m_controlState->onWheelScroll(dl); }

	inline glm::vec3 getLocalX() { return glm::normalize( getTransformMatrix() * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f) ); }
	inline glm::vec3 getLocalY() { return glm::normalize( getTransformMatrix() * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f) ); }
	inline glm::vec3 getLocalZ() { return glm::normalize( getTransformMatrix() * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f) ); }
	inline glm::vec3 getPosition() { return getTransformMatrix() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f); }

	Ray getRayGoingThroughMousePos();

	inline const glm::vec3& getTranslation() const { return m_translation; }
	inline void setTranslation(const glm::vec3& newTranslation) { m_translation = newTranslation; }

private:
	inline const glm::mat4& getTransformMatrix() { if (m_bMustRecomputeTransformMatrix) computeTransformMatrixAndItsInverse(); return m_transformMatrix; }

	void computeTransformMatrixAndItsInverse();

	template <typename T>
	inline void setControlState() {
		m_controlState = std::make_unique<T>(this);
	}

private:
	glm::mat4 m_transformMatrix;
	glm::mat4 m_inverseTransformMatrix;
	SphericalCoordinates m_sphereCoord;
	glm::vec3 m_translation;
	bool m_bMustRecomputeTransformMatrix;

	std::unique_ptr<CameraControlState> m_controlState;
};