#include "Renderer.hpp"

#include <SDL2/SDL.h>
#include <glad/glad.h>

#include "Debugging/gl-exception.h"

#include "Locator/Locate.hpp"
#include "Material/MaterialsManager.hpp"
#include "OpenGL/ShaderLibrary.hpp"

#include "OpenGL/SaveBufferMultisampled.hpp"

#include "Helper/File.hpp"

Renderer::Renderer(SDL_Window* window)
	: m_window(window), m_fullScreenRect(-1.0f, 1.0f, -1.0f, 1.0f),
	  m_clearColor(0.0f, 0.066f, 0.18f)
{
	onWindowResize();
}

void Renderer::initAfterApp() {
	m_lightingPassShaderLID = Locate::shaderLibrary().LoadShader(MyFile::rootDir + "/res/shaders/_lightingPass.vert", MyFile::rootDir + "/res/shaders/_lightingPass.frag");
	m_lightUniforms.addSubscriber(m_lightingPassShaderLID);
}

void Renderer::drawScene() {
	geometryPass();
	lightingPass();
}

void Renderer::geometryPass() {
	m_gBuffer.bind();
	GLCall(glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	Locate::materialsManager().draw();
	m_gBuffer.unbind();
}

void Renderer::lightingPass() {
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
	drawFullScreenQuad();
	// Detach textures
	m_gBuffer.albedoSpecularintensityTexture().detachAndUnbind();
	m_gBuffer.normalShininessTexture().detachAndUnbind();
	m_gBuffer.positionTexture().detachAndUnbind();
}

void Renderer::save(int width, int height, const std::string& filepath, int nbSamplesForMSAA) {
	SaveBufferMultisampled saveBuffer(width, height, nbSamplesForMSAA);
	m_gBuffer.setSize(width, height);
	saveBuffer.setViewport();
	geometryPass();
	saveBuffer.bind_WithoutSettingViewport();
	saveBuffer.clear();
	lightingPass();
	saveBuffer.save(filepath);
	saveBuffer.unbind();
	m_gBuffer.setSize(m_windowWidth, m_windowHeight);
}

void Renderer::drawFullScreenQuad() {
	m_fullScreenRect.binddrawunbind();
}

void Renderer::onWindowResize() {
	int w, h;
	SDL_GetWindowSize(m_window, &w, &h);
	// Update width and height
	m_windowWidth = w;
	m_windowHeight = h;
	// Update viewport
	glViewport(0, 0, w, h);
	// Update geometry buffer
	m_gBuffer.setSize(w, h);
}