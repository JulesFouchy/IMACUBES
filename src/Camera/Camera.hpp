#pragma once

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include "Helper/Display.hpp"
#include "Helper/SphericalCoordinates.hpp"

#include "CameraControlState.hpp"

#include "Debugging/Log.hpp"

#include "imgui/imgui.h"

#include <memory>

class Camera {
friend class CameraControlState_Rest;
friend class CameraControlState_Rotation;
public:
	Camera();
	~Camera() = default;

	inline const glm::mat4& getViewMatrix() { if(m_bMustRecomputeTransformMatrix) computeTransformMatrixAndItsInverse(); return m_inverseTransformMatrix; }
	inline const glm::mat4 getProjMatrix() { return glm::infinitePerspective(1.0f, Display::GetRatio(), 0.1f);  } // TODO return a reference to a member

	inline void update(float dt) { 
		ImGui::Begin("cam pos");
		ImGui::Text(std::to_string(m_sphereCoord.getAngleGround()).c_str()); ImGui::SameLine();
		ImGui::Text(std::to_string(m_sphereCoord.getAngleUp()).c_str());

		ImGui::Text(std::to_string(m_sphereCoord.getX()).c_str()); ImGui::SameLine();
		ImGui::Text(std::to_string(m_sphereCoord.getY()).c_str()); ImGui::SameLine();
		ImGui::Text(std::to_string(m_sphereCoord.getZ()).c_str());

		ImGui::End();
		//spdlog::warn("{} | {}", m_sphereCoord.getAngleGround(), m_sphereCoord.getAngleUp());
	m_controlState->update(dt); }

	inline void onWheelDown() { m_controlState->onWheelDown(); }
	inline void onWheelUp()   { m_controlState->onWheelUp();   }
	inline void onWheelScroll(float dl) { m_controlState->onWheelScroll(dl); }

private:
	void computeTransformMatrixAndItsInverse();

	template <typename T>
	inline void setControlState() {
		m_controlState = std::make_unique<T>(this);
	}

private:
	glm::mat4 m_transformMatrix;
	glm::mat4 m_inverseTransformMatrix;
	SphericalCoordinates m_sphereCoord;
	bool m_bMustRecomputeTransformMatrix;

	std::unique_ptr<CameraControlState> m_controlState;
};