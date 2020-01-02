#include "Renderer.hpp"

#include <SDL2/SDL.h>
#include <glad/glad.h>

Renderer::Renderer(SDL_Window* window)
	: m_window(window)
{
	onWindowResize();
}

void Renderer::onWindowResize() {
	int w, h;
	SDL_GetWindowSize(m_window, &w, &h);
	glViewport(0, 0, w, h);
	m_windowWidth = w;
	m_windowHeight = h;
}