#pragma once

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include "OpenGL/CubesGroup.hpp"
#include "OpenGL/Shader.hpp"
#include "Camera/Camera.hpp"
#include "History/HistoriesManager.hpp"
#include "CubesMap/CubesMap.hpp"
#include "Cursor/Cursor.hpp"
#include "GUI/SaveView.hpp"


class App {
friend class Locate;
private:
	App(SDL_Window* window);
	~App() = default;
public:
	void onInit();
	void onLoopIteration();

	void drawScene();
	void placeCursorJustBeforeHoveredCube();
	void ImGUI_DebugWindow();

	void onEvent();

private:
	Camera m_camera;
	HistoriesManager m_histories;
	CubesMap m_cubesMap;
	Cursor m_cursor;
	PopupWindow_SaveView m_saveViewWindow;
	Shader m_cursorShader;
	bool m_bShowImGUIDemoWindow;


/********************
  * INTERNAL CODE *
 ********************/

public:
	static void Initialize(SDL_Window* window);
	static void ShutDown();
	inline static App& Get() { return *m_instance; }

	void _loopIteration();

	inline SDL_Window* getWindow() const { return m_window; }
	inline bool isRunning() const { return m_running; }
	inline void exit() { m_running = false; }

private:
	static App* m_instance;

	SDL_Window* m_window;
	bool m_running;
};
