#include "Renderer.hpp"

#include <SDL2/SDL.h>
#include <glad/glad.h>

#include "Debugging/gl-exception.h"

#include "Locator/Locate.hpp"
#include "Material/MaterialsManager.hpp"
#include "OpenGL/ShaderLibrary.hpp"

#include "Helper/File.hpp"

Renderer::Renderer(SDL_Window* window)
	: m_window(window), m_fullScreenRect(-1.0f, 1.0f, -1.0f, 1.0f),
	  m_clearColor(0.0f, 0.066f, 0.18f)
{
	onWindowResize();
	m_gBuffer.initialize(m_windowWidth, m_windowHeight);
}

void Renderer::initAfterApp() {
	m_lightingPassShaderLID = Locate::shaderLibrary().LoadShader(MyFile::rootDir + "/res/shaders/_lightingPass.vert", MyFile::rootDir + "/res/shaders/_lightingPass.frag");
	m_lightUniforms.addSubscriber(m_lightingPassShaderLID);
}

void Renderer::drawScene() {
	m_gBuffer.bind();
	GLCall(glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	Locate::materialsManager().draw();
	m_gBuffer.unbind();

	GLCall(glClear(GL_DEPTH_BUFFER_BIT));

	// Attach textures
	m_gBuffer.positionTexture().attachToSlotAndBind();
	m_gBuffer.normalShininessTexture().attachToSlotAndBind();
	m_gBuffer.albedoSpecularintensityTexture().attachToSlotAndBind();
	// Send texture slots
	Locate::shaderLibrary()[m_lightingPassShaderLID].bind();
	Locate::shaderLibrary()[m_lightingPassShaderLID].setUniform1i("gPosInWorld", m_gBuffer.positionTexture().getSlot());
	Locate::shaderLibrary()[m_lightingPassShaderLID].setUniform1i("gNormalShininess", m_gBuffer.normalShininessTexture().getSlot());
	Locate::shaderLibrary()[m_lightingPassShaderLID].setUniform1i("gAlbedoSpec", m_gBuffer.albedoSpecularintensityTexture().getSlot());
	// Draw
	drawFullScreen();
	// Detach textures
	m_gBuffer.albedoSpecularintensityTexture().detachAndUnbind();
	m_gBuffer.normalShininessTexture().detachAndUnbind();
	m_gBuffer.positionTexture().detachAndUnbind();
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