#pragma once

struct SDL_Window;

class Renderer {
public:
	Renderer(SDL_Window* window);
	~Renderer() = default;

	inline float GetWidth() { return m_windowWidth; }
	inline float GetHeight() { return m_windowHeight; }
	inline float GetRatio() { return m_windowWidth / m_windowHeight; }

	void onWindowResize();

private:
	float m_windowWidth;
	float m_windowHeight;
	SDL_Window* m_window;
};