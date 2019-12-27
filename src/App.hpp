#pragma once

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include "OpenGL/CubesGroup.hpp"
#include "OpenGL/Shader.hpp"
#include "OpenGL/ShaderLibrary.hpp"
#include "OpenGL/UniformUpdateList.hpp"
#include "Camera/Camera.hpp"
#include "History/HistoriesManager.hpp"
#include "CubesMap/CubesMap.hpp"
#include "Cursor/Cursor.hpp"
#include "GUI/PopupWindow/SaveView.hpp"

#include "Light/LightsManager.hpp"


class App {
friend class Locate;
private:
	App(SDL_Window* window);
	~App() = default;
public:
	void onInit();
	void onLoopIteration();

	void drawScene();
	void placeCursorAtHoveredCube();

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
	CubesMap m_cubesMap;
	Cursor m_cursor;
	ShaderLibrary m_shaders;
	size_t m_cursorShaderLID;
	UniformUpdateList m_cameraUniforms;
	UniformUpdateList m_lightUniforms;
	glm::vec3 m_clearColor;
	LightsManager m_lightsManager;
	Camera m_camera;
	HistoriesManager m_histories;
	PopupWindow_SaveView m_saveViewWindow;
	bool m_bShowImGUIDemoWindow;


/********************
  * INTERNAL CODE *
 ********************/

public:
	static void Initialize(SDL_Window* window);
	static void ShutDown();
	inline static App& Get() { return *m_instance; }

	void _loopIteration();
	void handleSDLevents();

	inline SDL_Window* getWindow() const { return m_window; }
	inline bool isRunning() const { return m_running; }
	inline void exit() { m_running = false; }

private:
	static App* m_instance;

	SDL_Window* m_window;
	bool m_running;
};
