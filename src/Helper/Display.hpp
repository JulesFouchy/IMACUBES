#pragma once

#include <SDL2/SDL.h>

class Display {
public:
	static inline float GetWidth() { return m_width; }
	static inline float GetHeight() { return m_height; }
	static inline float GetRatio() { return m_width / m_height; }

	static void UpdateWindowSize(SDL_Window* window);

private:
	static float m_width;
	static float m_height;
};