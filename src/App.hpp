#pragma once

#include <SDL2/SDL.h>
#include <memory>

#include "OpenGL/CubesGroup.hpp"
#include "OpenGL/Shader.hpp"

#include "Core/Camera.hpp"

#include "History/History.hpp"

/**
 * @brief Base root of the app
 */
class App {
friend class Locate;
public:
	static void Initialize(SDL_Window* window);
	static void ShutDown();
	inline static App& Get() { return *m_instance; }

	SDL_Window* getWindow() const;
	bool isRunning() const;
	void exit();
private:
	App(SDL_Window* window);
	~App() = default;

public:
	void update();

private:
    void ImGUI_DebugWindow();
	void handleSDLEvents();

private:
	// Members
	Camera m_camera;
	History m_history;

	bool m_bShowImGUIDemoWindow;

	SDL_Window* m_window;
	bool m_running;

	// Singleton-ishy things
	static App* m_instance;
};
