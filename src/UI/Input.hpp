#pragma once

#include <SDL2/SDL.h>
#include "glm/glm.hpp"

#include "Keys.hpp"

class Input {

public:
	Input() = delete;
	~Input() = delete;
	static void Initialize();

	static glm::vec2 MousePositionInPixels();
	static glm::vec2 MousePositionInInches();
	static bool KeyIsDown(SpecialKey key);
	static bool KeyIsDown(char key);
	static bool KeyIsDown(SDL_Scancode key);

private:
	static float m_horizontalDPI;
	static float m_verticalDPI;
};