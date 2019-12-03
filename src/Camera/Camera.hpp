#pragma once

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include "Helper/Display.hpp"
#include "Helper/SphericalCoordinates.hpp"

#include "CameraControlState.hpp"

#include <memory>

class Camera {
friend class CameraControlState_Rest;
friend class CameraControlState_Rotation;
public:
	Camera();
	~Camera() = default;

	inline const glm::mat4& getViewMatrix() { return m_viewMatrix; }
	inline const glm::mat4 getProjMatrix() { return glm::perspective(1.0f, Display::GetRatio(), 0.1f, 10.0f);  }

private:
	template <typename T>
	void setControlState() {
		m_controlState = std::make_unique<T>(this);
	}

private:
	glm::mat4 m_viewMatrix;
	SphericalCoordinates m_sphereCoord;
	std::unique_ptr<CameraControlState> m_controlState;
};