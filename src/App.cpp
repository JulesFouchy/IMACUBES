#include "App.hpp"

#include <Debugging/Log.hpp>
#include <debug_break/debug_break.h>
#include <imgui.h>
#include <imgui/imgui_impl_sdl.h>
#include <imgui/imgui_impl_opengl3.h>
#include "OpenGL/gl-exception.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


bool App::m_instanciated = false;

App::App() : m_running(true), m_bShowImGUIDemoWindow(false), m_shader("res/shaders/standardLighting.vert", "res/shaders/standardLighting.frag", false)
{
    assert(!m_instanciated);
	m_instanciated = true;

	Log::Initialize();

	initSDL();
    initImgui();

	cubesData = CubesData(10, 10, 10);

	GLCall(glClearColor(0.4f, 0.6f, 0.95f, 1.0f));
	GLCall(glEnable(GL_DEPTH_TEST));

	// ----------------PLAYGROUND!------------------
	m_shader.compile();
	
	
	// Set uniform
	glm::mat4 projMat = glm::perspective(1.0f, 16.0f/9, 0.1f, 10.0f);
	m_shader.bind();
	m_shader.setUniformMat4f("u_projMat", projMat);
}

App::~App() {
    ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
    SDL_DestroyWindow(m_window);
	SDL_Quit();
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
	cubesData.draw();
	
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

void App::initImgui() const {
#if __APPLE__
	const char* glslVersion = "#version 150";
#else
	const char* glslVersion = "#version 130";
#endif
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(m_window, m_glContext);
	ImGui_ImplOpenGL3_Init(glslVersion);
	ImGui::StyleColorsClassic();
}

void App::initSDL() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
		spdlog::critical("[SDL2] Unable to initialize SDL: {}", SDL_GetError());
		debug_break();
	}
	SDL_GL_LoadLibrary(NULL);
#if __APPLE__
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
#else
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
#endif
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");

	m_window = SDL_CreateWindow(
		"IMACUBES",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		1280, 720,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
	);
	if (m_window == nullptr) {
		spdlog::critical("[SDL2] Window is null: {}", SDL_GetError());
		debug_break();
	}

	m_glContext = SDL_GL_CreateContext(m_window);
	if (m_glContext == nullptr) {
		spdlog::critical("[SDL2] OpenGL context is null: {}", SDL_GetError());
		debug_break();
	}

	SDL_GL_SetSwapInterval(1);

	if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
		spdlog::critical("[Glad] Glad not init");
		debug_break();
	}
}

/////////////////////////////////////////////////////////////////////////////
//////////////////////////// GETTERS & SETTERS //////////////////////////////
/////////////////////////////////////////////////////////////////////////////

SDL_Window* App::getWindow() const { return m_window; }
bool App::isRunning() const { return m_running; }
void App::exit() { m_running = false; }
