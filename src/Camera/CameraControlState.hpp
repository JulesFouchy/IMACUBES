#pragma once

#include <glm/glm.hpp>

#include "UI/Input.hpp"

class Camera;

class CameraControlState {
public:
	inline CameraControlState(Camera* camera)
		: m_camera(camera), m_mouseInitialPosInInches(Input::MousePositionInInches()) {}
	~CameraControlState() = default;
public:
	virtual void update(float dt) {};
	virtual void onWheelDown() {};
	virtual void onWheelUp() {};
protected:
	Camera* m_camera;
	glm::vec2 m_mouseInitialPosInInches;
};