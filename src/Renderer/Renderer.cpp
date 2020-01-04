#include "Renderer.hpp"

#include <SDL2/SDL.h>
#include <glad/glad.h>

#include "Debugging/gl-exception.h"

#include "Locator/Locate.hpp"
#include "Material/MaterialsManager.hpp"
#include "OpenGL/ShaderLibrary.hpp"
#include "CubesMap/CubesMap.hpp"

#include "OpenGL/SaveBufferMultisampled.hpp"

#include "Helper/File.hpp"

#include <imgui/imgui.h>

Renderer::Renderer(SDL_Window* window)
	: m_window(window), m_fullScreenRect(-1.0f, 1.0f, -1.0f, 1.0f),
	  m_whatToRender(WhatToRender::FinalImage),
	  m_bDenoiseNormals(true), m_denoiseNormalSamplingInverseOffset(2100.0f),
	  m_bUseAmbientOcclusion(true),
	  m_clearColor(0.0f, 0.066f, 0.18f, 1.0f)
{
	onWindowResize();
}

void Renderer::initAfterApp() {
	m_SSAOcomputer.initAfterApp();
	m_lightingPassShaderLID = Locate::shaderLibrary().LoadShader(MyFile::rootDir + "/res/shaders/_lightingPass.vert", MyFile::rootDir + "/res/shaders/_lightingPass.frag", false);
	setNumberOfLights(0, 0); // this compiles m_lightingPassShaderLID and #defines the number of lights
	Locate::shaderLibrary().addSubscriberToList(m_lightingPassShaderLID, UniformList::Lights);
	m_denoiseNormalsShaderLID = Locate::shaderLibrary().LoadShader(MyFile::rootDir + "/res/shaders/_texture.vert", MyFile::rootDir + "/res/shaders/_denoiseNormals.frag");
	m_blurSSAOtextureShaderLID = Locate::shaderLibrary().LoadShader(MyFile::rootDir + "/res/shaders/_texture.vert", MyFile::rootDir + "/res/shaders/_blur1ChannelTexture.frag");
}

void Renderer::drawScene() {
	geometryPass();
	if (m_bUseAmbientOcclusion)
		ssaoPass();
	renderOnScreenPass();
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

void Renderer::ssaoPass() {
	m_SSAOcomputer.compute();
	blurSSAOtexture(m_SSAOcomputer.texture());
}

void Renderer::lightingPass() {
	// Attach textures
	m_gBuffer.positionSpecularintensityTexture().attachToSlotAndBind();
	m_gBuffer.normalShininessTexture().attachToSlotAndBind();
	m_gBuffer.albedoTexture().attachToSlotAndBind();
	if (m_bUseAmbientOcclusion)
		m_SSAOcomputer.texture().attachToSlotAndBind();
	// Send texture slots
	Locate::shaderLibrary()[m_lightingPassShaderLID].bind();
	Locate::shaderLibrary()[m_lightingPassShaderLID].setUniform1i("gPosInWorld_SpecularIntensity", m_gBuffer.positionSpecularintensityTexture().getSlot());
	Locate::shaderLibrary()[m_lightingPassShaderLID].setUniform1i("gNormalShininess", m_gBuffer.normalShininessTexture().getSlot());
	Locate::shaderLibrary()[m_lightingPassShaderLID].setUniform1i("gAlbedo", m_gBuffer.albedoTexture().getSlot());
	// Ambient occlusion
	Locate::shaderLibrary()[m_lightingPassShaderLID].setUniform1i("u_bUseAmbientOcclusion", (int)m_bUseAmbientOcclusion);
	if (m_bUseAmbientOcclusion)
		Locate::shaderLibrary()[m_lightingPassShaderLID].setUniform1i("u_AmbientOcclusionMap", m_SSAOcomputer.texture().getSlot());
	// Draw
	drawFullScreenQuad();
	// Detach textures
	if (m_bUseAmbientOcclusion)
		m_SSAOcomputer.texture().detachAndUnbind();
	m_gBuffer.albedoTexture().detachAndUnbind();
	m_gBuffer.normalShininessTexture().detachAndUnbind();
	m_gBuffer.positionSpecularintensityTexture().detachAndUnbind();
}

void Renderer::renderOnScreenPass() {
	GLCall(glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	switch (m_whatToRender)
	{
	case WhatToRender::FinalImage:
		lightingPass();
		break;
	case WhatToRender::AlbedoMap:
		m_gBuffer.albedoTexture().showFullScreen(PixelFormat::RGB);
		break;
	case WhatToRender::NormalMap:
		m_gBuffer.normalShininessTexture().showFullScreen(PixelFormat::RGB, 2.0f/0.67f, 1.0f - 0.67f/2.0f);
		break;
	case WhatToRender::PositionMap:
		m_gBuffer.positionSpecularintensityTexture().showFullScreen(PixelFormat::RGB, std::max(std::max(Locate::cubesMap().width(), Locate::cubesMap().height()), Locate::cubesMap().depth()), 0.5f);
		break;
	case WhatToRender::AmbientOcclusionMap:
		m_SSAOcomputer.compute();
		m_SSAOcomputer.texture().showFullScreen();
		break;
	case WhatToRender::SpecularIntensityMap:
		m_gBuffer.positionSpecularintensityTexture().showFullScreen(PixelFormat::A);
		break;
	case WhatToRender::ShininessMap:
		m_gBuffer.normalShininessTexture().showFullScreen(PixelFormat::A, 128.0f);
		break;
	default:
		break;
	}
}

void Renderer::save(int width, int height, const std::string& filepath, int nbSamplesForMSAA) {
	SaveBufferMultisampled saveBuffer(width, height, nbSamplesForMSAA);
	m_gBuffer.setSize(width, height);
	if (m_bUseAmbientOcclusion)
		m_SSAOcomputer.setSize(width, height);
	saveBuffer.setViewport();
	geometryPass();
	if (m_bUseAmbientOcclusion)
		ssaoPass();
	saveBuffer.bind_WithoutSettingViewport();
	saveBuffer.clear();
	renderOnScreenPass();
	saveBuffer.save(filepath);
	saveBuffer.unbind();
	if (m_bUseAmbientOcclusion)
		m_SSAOcomputer.setSize(m_windowWidth, m_windowHeight);
	m_gBuffer.setSize(m_windowWidth, m_windowHeight);
}

void Renderer::denoiseNormals(Texture2D& texture, float samplingInverseOffset) {
	Shader& shader = Locate::shaderLibrary()[m_denoiseNormalsShaderLID];
	shader.bind();
	shader.setUniform1f("inverseOffset", samplingInverseOffset);
	drawOnTexture(texture, shader);
}

void Renderer::blurSSAOtexture(Texture2D& texture) {
	Shader& shader = Locate::shaderLibrary()[m_blurSSAOtextureShaderLID];
	shader.bind();
	drawOnTexture(texture, shader);
}

void Renderer::drawOnTexture(Texture2D& texture, Shader& shader) {
	m_postProcessBuffer.attachTexture(texture);
	texture.attachToSlotAndBind();
	shader.setUniform1i("u_TextureSlot", texture.getSlot());
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
	// Update SSAO buffer
	m_SSAOcomputer.setSize(w, h);
}

void Renderer::setNumberOfLights(int nbOfPointLights, int nbOfDirectionalLights) {
	std::vector<std::string> replaceMe = { "DEFINE_ME_nbPointLights", "DEFINE_ME_nbDirectionalLights" };
	std::vector<std::string> with = { std::to_string(nbOfPointLights),  std::to_string(nbOfDirectionalLights) };
	Locate::shaderLibrary()[m_lightingPassShaderLID].compile(replaceMe, with);
}

void Renderer::ImGui_Menu() {
	if (ImGui::BeginMenu("Background Color")) {
		ImGui::ColorPicker4("Background color", (float*)&m_clearColor);
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Render ")) {
		int item_current = (int)m_whatToRender;
		ImGui::PushID((int)&m_whatToRender);
		ImGui::Combo("", &item_current, " Final Image\0 Albedo Map\0 Normal Map\0 Position Map\0 Ambient Occlusion Map\0 Specular Intensity Map\0 Shininess Map\0\0");
		ImGui::PopID();
		m_whatToRender = (WhatToRender)item_current;
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Denoise normals")) {
		ImGui::Checkbox("Active", &m_bDenoiseNormals);
		ImGui::SliderFloat("Sampling inverse offset", &m_denoiseNormalSamplingInverseOffset, 500.0f, 3000.0f);
		ImGui::EndMenu();
	}	
	if (ImGui::BeginMenu("Ambient Occlusion")) {
		ImGui::Checkbox("Active", &m_bUseAmbientOcclusion);
		m_SSAOcomputer.ImGui_Parameters();
		ImGui::EndMenu();
	}
}