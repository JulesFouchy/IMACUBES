#pragma once

#include <SDL2/SDL.h>
#include <memory>

#include "OpenGL/CubesData.hpp"
#include "OpenGL/Shader.hpp"

/**
 * @brief Base root of the app
 */
class App {
public:
    App();
    ~App();

    void update();

public:
    SDL_Window* getWindow() const;
    bool isRunning() const;
    void exit();

private:
    void ImGUI_DebugWindow();
	void handleSDLEvents();

	void initImgui() const;
	void initSDL();

private:
    SDL_Window* m_window;
    SDL_GLContext m_glContext;
    static bool m_instanciated;
    bool m_running;
	bool m_bShowImGUIDemoWindow;

	// ----------------PLAYGROUND!------------------
	Shader m_shader;
	CubesData cubesData;
};
