#include "Display.hpp"
#include <glad/glad.h>

float Display::m_width;
float Display::m_height;

void Display::UpdateWindowSize(SDL_Window* window){
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	glViewport(0, 0, w, h);
	m_width = w;
	m_height = h;
}