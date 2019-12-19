#include "App.hpp"

#include <imgui.h>
#include <imgui/imgui_impl_sdl.h>
#include <imgui/imgui_impl_opengl3.h>
#include <glm/glm.hpp>

#include <Debugging/Log.hpp>
#include "Debugging/ImGuiLog.hpp"
#include "Debugging/gl-exception.h"

#include "Helper/Display.hpp"
#include "UI/Input.hpp"
#include "Locator/Locate.hpp"
#include "Material/MaterialsManager.hpp"
#include "CubeMaths/CubeMaths.hpp"


App::App(SDL_Window* window)
	: m_cubesMap(100, 100, 100), m_cursor(50, 50, 50), 
	  m_bShowImGUIDemoWindow(false),
	  m_window(window), m_running(true)
{
}


void App::onInit() {
	// ----------------PLAYGROUND!------------------
	Locate::materialsManager().addShader("res/shaders/default.vert", "res/shaders/testShader.frag");
	Locate::materialsManager().addShader("res/shaders/default.vert", "res/shaders/FlatColorPlusBorder.frag");
	Locate::materialsManager().updateMatrixUniform("u_projMat", m_camera.getProjMatrix());
	Locate::materialsManager().updateMatrixUniform("u_viewMat", m_camera.getViewMatrix());
}


void App::onLoopIteration() {
	// ImGui windows
	ImGUI_DebugWindow();
	if (m_bShowImGUIDemoWindow) // Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		ImGui::ShowDemoWindow(&m_bShowImGUIDemoWindow);

	// ----------------PLAYGROUND!------------------
	m_camera.update(1.0f / 60.0f);
	Locate::materialsManager().updateMatrixUniform("u_viewMat", m_camera.getViewMatrix());
	drawScene();
	m_cursor.draw();
	Locate::materialsManager().ImGui_Menu();
	m_histories.ImGuiWindow();
	m_saveViewWindow.Show_IfOpen();
}


void App::drawScene() {
	GLCall(glClearColor(0.4f, 0.6f, 0.95f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	Locate::materialsManager().draw();
}

void App::placeCursorJustBeforeHoveredCube(){
	Ray ray = m_camera.getRayGoingThroughMousePos();
	glm::ivec3 iPos = CubeMaths::CubeContaining(ray.origin);
	glm::ivec3 prevIpos = iPos;
	while (m_cubesMap.isIDvalid(iPos) && !m_cubesMap.cubeExists(iPos)) {
		float t = CubeMaths::IntersectionRayCube_WROIC(ray, iPos);
		ray.origin += (t + 0.01f) * ray.direction;
		iPos = CubeMaths::CubeContaining(ray.origin);
		if (m_cubesMap.isIDvalid(iPos) && !m_cubesMap.cubeExists(iPos))
			prevIpos = iPos;
	}
	if (m_cubesMap.isIDvalid(prevIpos)) {
		m_cursor.setPosition(prevIpos);
	}
}

void App::ImGUI_DebugWindow() {
	ImGui::Begin("Debug");
		ImGui::Checkbox("Show Demo Window", &m_bShowImGUIDemoWindow);
		ImGui::Text("Application average %.1f FPS", ImGui::GetIO().Framerate);
	ImGui::End();
}


void App::onEvent() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		ImGui_ImplSDL2_ProcessEvent(&e);
		switch (e.type) {
		case SDL_QUIT:
			exit();
			break;

		case SDL_MOUSEWHEEL:
			if (!ImGui::GetIO().WantCaptureMouse)
				m_camera.onWheelScroll(e.wheel.y);
			break;

		case SDL_MOUSEMOTION:
			if (!ImGui::GetIO().WantCaptureMouse)
				placeCursorJustBeforeHoveredCube();
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (!ImGui::GetIO().WantCaptureMouse) {
				if (e.button.button == SDL_BUTTON_MIDDLE)
					m_camera.onWheelDown();
				else if (e.button.button == SDL_BUTTON_LEFT) {
					m_cubesMap.addCube(m_cursor.getPosition());
					placeCursorJustBeforeHoveredCube();
				}
			}
			break;

		case SDL_MOUSEBUTTONUP:
			if (!ImGui::GetIO().WantCaptureMouse) {
				if (e.button.button == SDL_BUTTON_MIDDLE)
					m_camera.onWheelUp();
			}
			break;


		case SDL_KEYDOWN:

			if (!ImGui::GetIO().WantCaptureKeyboard) {

				if (Input::KeyIsDown(CTRL)) {
					if (e.key.keysym.sym == 'z') {
						m_histories.getActiveHistory().moveBackward();
					}
					else if (e.key.keysym.sym == 'y') {
						m_histories.getActiveHistory().moveForward();
					}
					else if (e.key.keysym.sym == 's') {
						m_saveViewWindow.Open();
					}
				}
				else {
					if (e.key.keysym.scancode == SDL_SCANCODE_F5) {
						Locate::materialsManager().Shaders()[Locate::materialsManager().SelectedMaterial().shaderID].reloadShader();
						Locate::materialsManager().updateMatrixUniform("u_projMat", m_camera.getProjMatrix());
						Locate::materialsManager().updateMatrixUniform("u_viewMat", m_camera.getViewMatrix());
					}
					Locate::history(HistoryType::Cubes).beginUndoGroup();
					if (e.key.keysym.sym == 'z') {
						m_cursor.setPosition(glm::ivec3(0, 1, 0) + m_cursor.getPosition());
					}
					else if (e.key.keysym.sym == 's') {
						m_cursor.setPosition(glm::ivec3(0, -1, 0) + m_cursor.getPosition());
					}
					else if (e.key.keysym.sym == 'q') {
						m_cursor.setPosition(glm::ivec3(1, 0, 0) + m_cursor.getPosition());
					}
					else if (e.key.keysym.sym == 'd') {
						m_cursor.setPosition(glm::ivec3(-1, 0, 0) + m_cursor.getPosition());
					}
					else if (e.key.keysym.sym == 'w') {
						m_cursor.setPosition(glm::ivec3(0, 0, 1) + m_cursor.getPosition());
					}
					else if (e.key.keysym.sym == 'x') {
						m_cursor.setPosition(glm::ivec3(0, 0, -1) + m_cursor.getPosition());
					}
					Locate::history(HistoryType::Cubes).endUndoGroup();
				}
			}
			break;

		case SDL_KEYUP:
			if (!ImGui::GetIO().WantCaptureKeyboard) {

			}
			break;

		case SDL_WINDOWEVENT:
			switch (e.window.event) {
			case SDL_WINDOWEVENT_RESIZED:
				// get new width and height and update the viewport
				Display::UpdateWindowSize(m_window);
				// Update camera's ratio
				Locate::materialsManager().updateMatrixUniform("u_projMat", m_camera.getProjMatrix());
				break;
			}

		default:
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
///////////////////////////// INTERNAL CODE /////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

App* App::m_instance = nullptr;

void App::Initialize(SDL_Window* window) {
	assert(!m_instance);
	m_instance = new App(window);
}

void App::ShutDown() {
	delete m_instance;
}

void App::_loopIteration() {
	// Events
	onEvent();
	// Start ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_window);
	ImGui::NewFrame();

	// Actual application code
	onLoopIteration();

	// Render ImGui
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// End frame
	SDL_GL_SwapWindow(m_window);
}