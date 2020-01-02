#include "Renderer.hpp"

#include <SDL2/SDL.h>
#include <glad/glad.h>

#include "Debugging/gl-exception.h"

#include "Material/MaterialsManager.hpp"
#include "Locator/Locate.hpp"

Renderer::Renderer(SDL_Window* window)
	: m_window(window),
	  m_clearColor(0.0f, 0.066f, 0.18f)
{
	onWindowResize();
	m_fullScreenRect.initialize(getRatio(), ZERO_TO_ONE__ZERO_TO_ONE);
	m_gBuffer.initialize(m_windowWidth, m_windowHeight);
}

void Renderer::drawScene() {
	GLCall(glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	//m_gBuffer.bind();
	Locate::materialsManager().draw();
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