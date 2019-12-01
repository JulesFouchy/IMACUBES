#pragma once

#include <SDL2/SDL.h>
#include <memory>

#include "OpenGL/CubesGroup.hpp"
#include "OpenGL/Shader.hpp"

#include "Core/Camera.hpp"

/**
 * @brief Base root of the app
 */
class App {
public:
    App(SDL_Window* window);
    ~App() = default;

    void update();

public:
    SDL_Window* getWindow() const;
    bool isRunning() const;
    void exit();

private:
    void ImGUI_DebugWindow();
	void handleSDLEvents();

private:
	SDL_Window* m_window;
    static bool m_instanciated;
    bool m_running;
	bool m_bShowImGUIDemoWindow;

	Camera m_camera;

	// ----------------PLAYGROUND!------------------
};
