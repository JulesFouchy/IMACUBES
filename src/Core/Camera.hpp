#pragma once

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include "Helper/Display.hpp"

class Camera {
public:
	Camera() = default;
	~Camera() = default;

	//inline const glm::mat4& getInverseViewMatrix() return 
	inline const glm::mat4 getProjMatrix() { return glm::perspective(1.0f, Display::GetRatio(), 0.1f, 10.0f);  }

private:

};