#pragma once

#include <SDL2/SDL.h>
#include <memory>

#include "OpenGL/CubesGroup.hpp"
#include "OpenGL/Shader.hpp"

#include "Camera/Camera.hpp"
#include "History/History.hpp"
#include "CubesMap/CubesMap.hpp"
#include "GUI/SaveView.hpp"

#include <glm/glm.hpp>

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
	~App() {};

public:
	void drawScene();
	void onInit();
	void mainLoopIteration();

private:
    void ImGUI_DebugWindow();
	void handleSDLEvents();

private:
	// Members
	Camera m_camera;
	History m_history;
	CubesMap m_cubesMap;
	PopupWindow_SaveView m_saveViewWindow;
	glm::vec3 m_pos = glm::vec3(50.0f);
	//
	bool m_bShowImGUIDemoWindow;

	SDL_Window* m_window;
	bool m_running;

	// Singleton-ishy things
	static App* m_instance;
};
