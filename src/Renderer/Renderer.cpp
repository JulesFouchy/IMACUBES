#include "Renderer.hpp"

#include <SDL2/SDL.h>
#include <glad/glad.h>

#include "Debugging/gl-exception.h"

#include "Locator/Locate.hpp"
#include "Material/MaterialsManager.hpp"
#include "OpenGL/ShaderLibrary.hpp"

#include "OpenGL/SaveBufferMultisampled.hpp"

#include "Helper/File.hpp"

#include <imgui/imgui.h>

Renderer::Renderer(SDL_Window* window)
	: m_window(window), m_fullScreenRect(-1.0f, 1.0f, -1.0f, 1.0f),
	  m_bDenoiseNormals(true), m_denoiseNormalSamplingInverseOffset(2100.0f),
	  m_clearColor(0.0f, 0.066f, 0.18f)
{
	onWindowResize();
}

void Renderer::initAfterApp() {
	m_lightingPassShaderLID = Locate::shaderLibrary().LoadShader(MyFile::rootDir + "/res/shaders/_lightingPass.vert", MyFile::rootDir + "/res/shaders/_lightingPass.frag");
	m_lightUniforms.addSubscriber(m_lightingPassShaderLID);
	m_blurShaderLID = Locate::shaderLibrary().LoadShader(MyFile::rootDir + "/res/shaders/_texture.vert", MyFile::rootDir + "/res/shaders/_denoiseNormals.frag");
}

void Renderer::drawScene() {
	geometryPass();
	lightingPass();
}

void Renderer::geometryPass() {
	m_gBuffer.bind();
	GLCall(glClearColor(0.0f,0.0f,0.0f,0.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	Locate::materialsManager().draw();
	m_gBuffer.unbind();
	if (m_bDenoiseNormals) {
		denoiseNormals(m_gBuffer.normalShininessTexture(), m_denoiseNormalSamplingInverseOffset);
	}
}

void Renderer::lightingPass() {
	GLCall(glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, 0.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	//if(bShowNormals)
	//	m_gBuffer.normalShininessTexture().showFullScreen();
	//else {
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
	//}
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

void Renderer::denoiseNormals(Texture2D& texture, float samplingInverseOffset) {
	m_postProcessBuffer.attachTexture(texture);
	texture.attachToSlotAndBind();
	Locate::shaderLibrary()[m_blurShaderLID].bind();
	Locate::shaderLibrary()[m_blurShaderLID].setUniform1i("u_TextureSlot", texture.getSlot());
	Locate::shaderLibrary()[m_blurShaderLID].setUniform1f("inverseOffset", samplingInverseOffset);
	m_postProcessBuffer.bind();
	drawFullScreenQuad();
	m_postProcessBuffer.unbind();
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

void Renderer::ImGui_Menu() {
	if (ImGui::BeginMenu("Background Color")) {
		ImGui::ColorPicker3("Background color", (float*)&m_clearColor);
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Denoise normals")) {
		ImGui::Checkbox("Active", &m_bDenoiseNormals);
		ImGui::SliderFloat("Sampling inverse offset", &m_denoiseNormalSamplingInverseOffset, 1500.0f, 3000.0f);
		ImGui::EndMenu();
	}
}