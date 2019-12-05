#pragma once

#include "CameraControlState.hpp"
#include "Camera.hpp"

class CameraControlState_Rest : public CameraControlState {
public:
	CameraControlState_Rest(Camera* camera);
	~CameraControlState_Rest() = default;

	void onWheelDown() override;
	void onWheelScroll(float dl) override;
};