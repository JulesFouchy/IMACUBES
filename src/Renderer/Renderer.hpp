#pragma once

#include <glm/glm.hpp>

#include "OpenGL/RectVAO.hpp"
#include "GeometryBuffer.hpp"

struct SDL_Window;

class Renderer {
public:
	Renderer(SDL_Window* window);
	~Renderer() = default;

	void drawScene();
	void drawFullScreen();

	void onWindowResize();

	inline float getWidth() { return m_windowWidth; }
	inline float getHeight() { return m_windowHeight; }
	inline float getRatio() { return m_windowWidth / m_windowHeight; }

	inline float* clearColorPtr() { return (float*) &m_clearColor; }

private:
	float m_windowWidth;
	float m_windowHeight;
	SDL_Window* m_window;

	RectVAO m_fullScreenRect;

	GeometryBuffer m_gBuffer;
	glm::vec3 m_clearColor;
};