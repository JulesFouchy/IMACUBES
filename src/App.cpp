#include "App.hpp"

#include <Debugging/Log.hpp>
#include <imgui.h>
#include <imgui/imgui_impl_sdl.h>
#include <imgui/imgui_impl_opengl3.h>
#include "OpenGL/gl-exception.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


bool App::m_instanciated = false;

App::App(SDL_Window* window) : m_window(window), m_running(true), m_bShowImGUIDemoWindow(false),
							   m_shader("res/shaders/standardLighting.vert", "res/shaders/standardLighting.frag", false), cubesData(10, 10, 10)
{
    assert(!m_instanciated);
	m_instanciated = true;

	Log::Initialize();

	GLCall(glClearColor(0.4f, 0.6f, 0.95f, 1.0f));
	GLCall(glEnable(GL_DEPTH_TEST));

	// ----------------PLAYGROUND!------------------
	m_shader.compile();
	
	// Set uniform
	glm::mat4 projMat = glm::perspective(1.0f, 16.0f/9, 0.1f, 10.0f);
	m_shader.bind();
	m_shader.setUniformMat4f("u_projMat", projMat);
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
	
	m_shader.bind();
	cubesData.drawWireframe();
	
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

		case SDL_WINDOWEVENT:
			switch (e.window.event) {
			case SDL_WINDOWEVENT_RESIZED:
				// get new width and height and update the viewport
				int w, h;
				SDL_GetWindowSize(m_window, &w, &h);
				GLCall(glViewport(0, 0, w, h));
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
