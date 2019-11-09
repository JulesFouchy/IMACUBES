#pragma once

#include <SDL2/SDL.h>
#include <memory>


#include <glad/glad.h>
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
#if __APPLE__
	const char* m_glsl_version = "#version 150";
#else
	const char* m_glsl_version = "#version 130";
#endif
    SDL_Window* m_window;
    SDL_GLContext m_glContext;
    static bool m_instanciated;
    bool m_running;
	bool m_bShowImGUIDemoWindow;

	// ----------------PLAYGROUND!------------------
	GLuint m_vboID;
	GLuint m_iboID;
	Shader m_shader;
};