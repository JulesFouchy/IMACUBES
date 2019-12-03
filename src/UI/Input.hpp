#pragma once

#include <SDL2/SDL.h>
#include "glm/glm.hpp"

#include "Keys.hpp"

class Input {

public:
	Input() = delete;
	~Input() = delete;

	//static glm::vec2 GetMousePosition();
	static bool KeyIsDown(Key key);
};