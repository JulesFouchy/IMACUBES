#include "App.hpp"

#include <Debugging/Log.hpp>
#include <imgui.h>
#include <imgui/imgui_impl_sdl.h>
#include <imgui/imgui_impl_opengl3.h>
#include "OpenGL/gl-exception.h"
#include "Helper/Display.hpp"

#include <glm/glm.hpp>

#include "OpenGL/Uniform/UniformFactory.hpp"

#include "Core/MaterialsManager.hpp"

bool App::m_instanciated = false;

App::App(SDL_Window* window) : m_window(window), m_running(true), m_bShowImGUIDemoWindow(false)
{
    assert(!m_instanciated);
	m_instanciated = true;

	Log::Initialize();

	Display::UpdateWindowSize(m_window);

	GLCall(glClearColor(0.4f, 0.6f, 0.95f, 1.0f));
	GLCall(glEnable(GL_DEPTH_TEST));

	// ----------------PLAYGROUND!------------------
	
	//MaterialsManager::m_shadersList.reserve(10);
	MaterialsManager::addShader("res/shaders/testShader.vert", "res/shaders/testShader.frag");
	MaterialsManager::addShader("res/shaders/standardLighting.vert", "res/shaders/testShader.frag");
	MaterialsManager::updateMatrixUniform("u_projMat", m_camera.getProjMatrix());
}

/////////////////////////////////////////////////////////////////////////////
////////////////////////////// PUBLIC METHODS ///////////////////////////////
/////////////////////////////////////////////////////////////////////////////


void App::update() {
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	// Feed inputs
	handleSDLEvents();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_window);
	ImGui::NewFrame();

	// ImGui windows
	ImGUI_DebugWindow();
	if (m_bShowImGUIDemoWindow) // Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		ImGui::ShowDemoWindow(&m_bShowImGUIDemoWindow);

	// ----------------PLAYGROUND!------------------
	
	MaterialsManager::draw();
	MaterialsManager::ImGui_Menu();
	
	// ---------------------------------------------

	// Render ImGui
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// Reset input deltas
	SDL_GL_SwapWindow(m_window);
}

/////////////////////////////////////////////////////////////////////////////
///////////////////////////// PRIVATE METHODS ///////////////////////////////
/////////////////////////////////////////////////////////////////////////////


void App::ImGUI_DebugWindow() {
	ImGui::Begin("Debug");

	ImGui::Checkbox("Show Demo Window", &m_bShowImGUIDemoWindow);
	ImGui::Text("Application average %.1f FPS", ImGui::GetIO().Framerate);

	ImGui::End();
}

void App::handleSDLEvents() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		ImGui_ImplSDL2_ProcessEvent(&e);
		switch (e.type) {
		case SDL_QUIT:
			exit();
			break;

		case SDL_MOUSEWHEEL:
			break;

		case SDL_MOUSEMOTION:
			break;

		case SDL_MOUSEBUTTONDOWN:
			break;

		case SDL_MOUSEBUTTONUP:
			break;


		case SDL_KEYDOWN:
			if (e.key.keysym.scancode == SDL_SCANCODE_F5) {
				MaterialsManager::Shaders()[MaterialsManager::SelectedMaterial().shaderID].reloadShader();
				MaterialsManager::updateMatrixUniform("u_projMat", m_camera.getProjMatrix());
			}
			break;

		case SDL_WINDOWEVENT:
			switch (e.window.event) {
			case SDL_WINDOWEVENT_RESIZED:
				// get new width and height and update the viewport
				Display::UpdateWindowSize(m_window);
				// Update camera's ratio
				MaterialsManager::updateMatrixUniform("u_projMat", m_camera.getProjMatrix());
				break;
			}

		default:
			break;
		}
	}

	if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow)) {

	}
}

/////////////////////////////////////////////////////////////////////////////
//////////////////////////// GETTERS & SETTERS //////////////////////////////
/////////////////////////////////////////////////////////////////////////////

SDL_Window* App::getWindow() const { return m_window; }
bool App::isRunning() const { return m_running; }
void App::exit() { m_running = false; }
