#pragma once

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include "Camera/Camera.hpp"
#include "CubesMap/CubesMap.hpp"
#include "Cursor/Cursor.hpp"
#include "GUI/PopupWindow/SaveView.hpp"
#include "History/HistoriesManager.hpp"
#include "Light/LightsManager.hpp"
#include "OpenGL/CubesGroup.hpp"
#include "OpenGL/Shader.hpp"
#include "OpenGL/ShaderLibrary.hpp"
#include "Renderer/Renderer.hpp"
#include "Tools/ToolsManager.hpp"

class App {
    friend class Locate;

private:
    App(SDL_Window* window);
    ~App() = default;

public:
    void onInit();
    void onLoopIteration();

    void onViewMatrixChange();
    void onProjMatrixChange();

    void onEvent(const SDL_Event& e);

    // The ImGui functions are in AppGUI.cpp
    void ImGui_DebugWindow();
    void _ImGui_CameraControls();
    void _ImGui_CameraView();
    void ImGui_MainMenuBar();
    void ImGui_RightSideWindow();
    // --------------------------------------

private:
    glm::ivec3 getFirstEmptyCubeOnTop(glm::ivec3 pos);

private:
    Renderer             m_renderer;
    CubesMap             m_cubesMap;
    Cursor               m_cursor;
    ShaderLibrary        m_shaderLibrary;
    size_t               m_cursorShaderLID;
    LightsManager        m_lightsManager;
    ToolsManager         m_toolsManager;
    Camera               m_camera;
    HistoriesManager     m_histories;
    PopupWindow_SaveView m_saveViewWindow;
    bool                 m_bShowImGUIDemoWindow;
    bool                 m_bAddTheSelectedSomething;

    /********************
     * INTERNAL CODE *
     ********************/

public:
    static void        Initialize(SDL_Window* window);
    static void        ShutDown();
    inline static App& Get() { return *m_instance; }

    void _loopIteration();
    void handleSDLevents();

    inline SDL_Window* getWindow() const { return m_window; }
    inline bool        isRunning() const { return m_running; }
    inline void        exit() { m_running = false; }

private:
    static App* m_instance;

    SDL_Window* m_window;
    bool        m_running;
};
