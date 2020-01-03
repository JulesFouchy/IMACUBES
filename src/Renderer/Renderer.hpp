#pragma once

#include <glm/glm.hpp>

#include "OpenGL/RectVAO.hpp"
#include "GeometryBuffer.hpp"
#include "SSAOcomputer.hpp"
#include "OpenGL/Uniform/UniformUpdateList.hpp"
#include "OpenGL/FrameBuffer.hpp"

#include <string>

enum class WhatToRender {
	FinalImage,
	AlbedoMap,
	NormalMap,
	PositionMap,
	SpecularIntensityMap,
	ShininessMap,
};

struct SDL_Window;

class Renderer {
friend class App;
public:
	Renderer(SDL_Window* window);
	void initAfterApp();
	~Renderer() = default;

	void drawScene();
	void geometryPass();
	void lightingPass();
	void renderOnScreenPass();
	void save(int width, int height, const std::string& filepath, int nbSamplesForMSAA = 4);

	void denoiseNormals(Texture2D& texture, float samplingInverseOffset);

	void drawFullScreenQuad();

	void onWindowResize();

	inline UniformUpdateList& cameraUniforms() { return m_cameraUniforms; }
	inline UniformUpdateList& lightUniforms() { return m_lightUniforms; }

	inline float getWidth() { return m_windowWidth; }
	inline float getHeight() { return m_windowHeight; }
	inline float getRatio() { return m_windowWidth / m_windowHeight; }

	void ImGui_Menu();

private:
	float m_windowWidth;
	float m_windowHeight;
	SDL_Window* m_window;

	RectVAO m_fullScreenRect;

	UniformUpdateList m_cameraUniforms;
	UniformUpdateList m_lightUniforms;

	GeometryBuffer m_gBuffer;
	size_t m_lightingPassShaderLID;
	SSAOcomputer m_SSAOcomputer;
	WhatToRender m_whatToRender;

	FrameBuffer m_postProcessBuffer;
	size_t m_denoiseNormalsShaderLID;
	bool m_bDenoiseNormals;
	float m_denoiseNormalSamplingInverseOffset;

	glm::vec4 m_clearColor;
};