#include "Renderer.hpp"

#include <SDL2/SDL.h>
#include <glad/glad.h>

#include "Debugging/gl-exception.h"

#include "Locator/Locate.hpp"
#include "Material/MaterialsManager.hpp"
#include "OpenGL/ShaderLibrary.hpp"

#include "OpenGL/SaveBufferMultisampled.hpp"

#include "OpenGL/FrameBuffer.hpp"

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
	m_blurShaderLID = Locate::shaderLibrary().LoadShader(MyFile::rootDir + "/res/shaders/_texture.vert", MyFile::rootDir + "/res/shaders/_removeIsolatedNoiseOnTexture.frag");
}

#include <imgui/imgui.h>
void Renderer::drawScene() {
	geometryPass();
	//m_gBuffer.normalShininessTexture().showFullScreen();
	lightingPass();
}

void Renderer::geometryPass() {
	static bool bBlurNormals = true;
	static float invertOffset = 2100;
	ImGui::Begin("blur");
	ImGui::Checkbox("Blur normals", &bBlurNormals);
	ImGui::SliderFloat("Inverse offset", &invertOffset, 1000, 3000);
	ImGui::End();

	m_gBuffer.bind();
	GLCall(glClearColor(0.0f,0.0f,0.0f,0.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	Locate::materialsManager().draw();
	m_gBuffer.unbind();
	if (bBlurNormals) {
		blur(m_gBuffer.normalShininessTexture(), invertOffset);
	}
}

void Renderer::lightingPass() {
	static bool bShowNormals = false;
	ImGui::Begin("show norm");
	ImGui::Checkbox("Show normals", &bShowNormals);
	ImGui::End();


	GLCall(glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, 0.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	if(bShowNormals)
		m_gBuffer.normalShininessTexture().showFullScreen();
	else {
		// Attach textures
		m_gBuffer.positionSpecularintensityTexture().attachToSlotAndBind();
		m_gBuffer.normalShininessTexture().attachToSlotAndBind();
		m_gBuffer.albedoTexture().attachToSlotAndBind();
		// Send texture slots
		Locate::shaderLibrary()[m_lightingPassShaderLID].bind();
		Locate::shaderLibrary()[m_lightingPassShaderLID].setUniform1i("gPosInWorld_SpecularIntensity", m_gBuffer.positionSpecularintensityTexture().getSlot());
		Locate::shaderLibrary()[m_lightingPassShaderLID].setUniform1i("gNormalShininess", m_gBuffer.normalShininessTexture().getSlot());
		Locate::shaderLibrary()[m_lightingPassShaderLID].setUniform1i("gAlbedo", m_gBuffer.albedoTexture().getSlot());
		// Draw
		drawFullScreenQuad();
		// Detach textures
		m_gBuffer.albedoTexture().detachAndUnbind();
		m_gBuffer.normalShininessTexture().detachAndUnbind();
		m_gBuffer.positionSpecularintensityTexture().detachAndUnbind();
	}
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

void Renderer::blur(Texture2D& texture, float inverseOffset) {
	FrameBuffer postProcessBuffer(texture);
	texture.attachToSlotAndBind();
	Locate::shaderLibrary()[m_blurShaderLID].bind();
	Locate::shaderLibrary()[m_blurShaderLID].setUniform1i("u_TextureSlot", texture.getSlot());
	Locate::shaderLibrary()[m_blurShaderLID].setUniform1f("inverseOffset", inverseOffset);
	postProcessBuffer.bind();
	drawFullScreenQuad();
	postProcessBuffer.unbind();
	texture.detachAndUnbind();
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