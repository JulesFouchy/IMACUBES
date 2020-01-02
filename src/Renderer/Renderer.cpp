#include "Renderer.hpp"

#include <SDL2/SDL.h>
#include <glad/glad.h>

#include "Debugging/gl-exception.h"

#include "Material/MaterialsManager.hpp"
#include "Locator/Locate.hpp"

#include "OpenGL/ShaderLibrary.hpp"

Renderer::Renderer(SDL_Window* window)
	: m_window(window), m_fullScreenRect(-1.0f, 1.0f, -1.0f, 1.0f),
	  m_clearColor(0.0f, 0.066f, 0.18f)
{
	onWindowResize();
	m_gBuffer.initialize(m_windowWidth, m_windowHeight);
}

void Renderer::drawScene() {
	m_gBuffer.bind();
	GLCall(glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	Locate::materialsManager().draw();
	m_gBuffer.unbind();

	GLCall(glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	m_gBuffer.getPositionTexture().showFullScreen();
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