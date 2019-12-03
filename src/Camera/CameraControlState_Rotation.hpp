#pragma once

#include "CameraControlState.hpp"
#include "Camera.hpp"

class CameraControlState_Rotation : public CameraControlState {
public:
	CameraControlState_Rotation(Camera* camera);
	~CameraControlState_Rotation() = default;

	void onWheelUp() override;
};