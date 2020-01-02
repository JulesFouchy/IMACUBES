#pragma once

#include <glm/glm.hpp>

#include "OpenGL/RectVAO.hpp"
#include "GeometryBuffer.hpp"
#include "OpenGL/Uniform/UniformUpdateList.hpp"

#include <string>

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
	void save(int width, int height, const std::string& filepath, int nbSamplesForMSAA = 4);

	void blur(Texture2D& texture, float inverseOffset);

	void drawFullScreenQuad();

	void onWindowResize();

	inline UniformUpdateList& cameraUniforms() { return m_cameraUniforms; }
	inline UniformUpdateList& lightUniforms() { return m_lightUniforms; }

	inline float getWidth() { return m_windowWidth; }
	inline float getHeight() { return m_windowHeight; }
	inline float getRatio() { return m_windowWidth / m_windowHeight; }

	inline float* clearColorPtr() { return (float*) &m_clearColor; }

private:
	float m_windowWidth;
	float m_windowHeight;
	SDL_Window* m_window;

	RectVAO m_fullScreenRect;
	size_t m_blurShaderLID;

	UniformUpdateList m_cameraUniforms;
	UniformUpdateList m_lightUniforms;

	GeometryBuffer m_gBuffer;
	size_t m_lightingPassShaderLID;

	glm::vec3 m_clearColor;
};