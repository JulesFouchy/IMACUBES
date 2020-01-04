#pragma once

#include <glm/glm.hpp>

#include "OpenGL/RectVAO.hpp"
#include "GeometryBuffer.hpp"
#include "SSAOcomputer.hpp"
#include "OpenGL/Uniform/UniformUpdateList.hpp"
#include "OpenGL/FrameBuffer.hpp"

#include "ShadowMapBuffer.hpp"

#include <string>

enum class WhatToRender {
	FinalImage,
	AlbedoMap,
	NormalMap,
	PositionMap,
	AmbientOcclusionMap,
	ShadowMap,
	SpecularIntensityMap,
	ShininessMap,
};

struct SDL_Window;

class Renderer {
friend class App;
friend class SSAOcomputer;
public:
	Renderer(SDL_Window* window);
	void initAfterApp();
	~Renderer() = default;

	void drawScene();
	void geometryPass();
	void ssaoPass();
	void shadowPass();
	void lightingPass();
	void renderOnScreenPass();
	void save(int width, int height, const std::string& filepath, int nbSamplesForMSAA = 4);

	void denoiseNormals(Texture2D& texture, float samplingInverseOffset);
	void blurSSAOtexture(Texture2D& texture);
	void drawOnTexture(Texture2D& texture, Shader& shader);

	void drawFullScreenQuad();

	void onWindowResize();

	void setNumberOfLights(int nbOfPointLights, int nbOfDirectionalLights);

	inline float getWidth() { return m_windowWidth; }
	inline float getHeight() { return m_windowHeight; }
	inline float getRatio() { return m_windowWidth / m_windowHeight; }

	void ImGui_Menu();

private:
	float m_windowWidth;
	float m_windowHeight;
	SDL_Window* m_window;

	RectVAO m_fullScreenRect;

	GeometryBuffer m_gBuffer;
	size_t m_lightingPassShaderLID;
	SSAOcomputer m_SSAOcomputer;
	ShadowMapBuffer m_shadowMapBuffer;

	WhatToRender m_whatToRender;

	FrameBuffer m_postProcessBuffer;
	size_t m_denoiseNormalsShaderLID;
	size_t m_blurSSAOtextureShaderLID;
	bool m_bDenoiseNormals;
	float m_denoiseNormalSamplingInverseOffset;
	bool m_bUseAmbientOcclusion;

	glm::vec4 m_clearColor;
};