#include "Renderer.hpp"

#include <SDL2/SDL.h>
#include <glad/glad.h>

Renderer::Renderer(SDL_Window* window)
	: m_window(window)
{
	onWindowResize();
	m_fullScreenRect.initialize(getRatio(), ZERO_TO_ONE__ZERO_TO_ONE);
	m_gBuffer.initialize(m_windowWidth, m_windowHeight);
}

void Renderer::drawFullScreen() {
	m_fullScreenRect.binddrawunbind();
}

void Renderer::onWindowResize() {
	int w, h;
	SDL_GetWindowSize(m_window, &w, &h);
	glViewport(0, 0, w, h);
	m_windowWidth = w;
	m_windowHeight = h;
}