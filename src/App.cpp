#include "App.hpp"

#include <imgui.h>
#include <imgui/imgui_impl_sdl.h>
#include <imgui/imgui_impl_opengl3.h>
#include <glm/glm.hpp>

#include "Debugging/Log.hpp"
#include "Debugging/ImGuiLog.hpp"
#include "Debugging/gl-exception.h"

#include "Helper/Display.hpp"
#include "UI/Input.hpp"
#include "UI/Settings.hpp"
#include "Locator/Locate.hpp"
#include "Material/MaterialsManager.hpp"
#include "CubeMaths/CubeMaths.hpp"

#include <algorithm>


App::App(SDL_Window* window)
	: m_cubesMap(100, 100, 100), m_cursor(), m_cursorShader("res/shaders/cursor.vert", "res/shaders/cursor.frag"),
	  m_camera(glm::vec3(m_cubesMap.width()/2, m_cubesMap.height()/2, m_cubesMap.depth()/2)),
	  m_bShowImGUIDemoWindow(false),
	  m_window(window), m_running(true)
{
}


void App::onInit() {
	// ----------------PLAYGROUND!------------------
	m_cursor = Cursor(m_cubesMap.width()/2, m_cubesMap.height()/2, m_cubesMap.depth()/2);
	Locate::materialsManager().addShader("res/shaders/default.vert", "res/shaders/FlatColorPlusBorder.frag");
	Locate::materialsManager().addShader("res/shaders/default.vert", "res/shaders/testShader.frag");
	Locate::materialsManager().updateMatrixUniform("u_projMat", m_camera.getProjMatrix());
	Locate::materialsManager().updateMatrixUniform("u_viewMat", m_camera.getViewMatrix());
	m_cursorShader.bind();
	m_cursorShader.setUniformMat4f("u_projMat", m_camera.getProjMatrix());
	m_cursorShader.setUniformMat4f("u_viewMat", m_camera.getViewMatrix());

	Locate::history(HistoryType::Cubes).beginUndoGroup();
	for (int x = m_cubesMap.width()*0.2; x < m_cubesMap.width()*0.8; ++x) {
		for (int z = m_cubesMap.depth()*0.2; z < m_cubesMap.depth()*0.8; ++z) {
			for (int y = std::max((int)m_cubesMap.height()/2 - 5, 0); y < m_cubesMap.height()/2; ++y) {
				m_cubesMap.addCube(glm::ivec3(x, y, z));
			}
		}
	}
	Locate::history(HistoryType::Cubes).endUndoGroup();
}


void App::onLoopIteration() {
	// ImGui windows
	ImGui_DebugWindow();
	ImGui_Settings();
	ImGui_Camera();
	if (m_bShowImGUIDemoWindow) // Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		ImGui::ShowDemoWindow(&m_bShowImGUIDemoWindow);
	ImGui_MainMenuBar();

	// ----------------PLAYGROUND!------------------
	m_camera.update(1.0f / 60.0f);
	Locate::materialsManager().updateMatrixUniform("u_viewMat", m_camera.getViewMatrix());
	m_cursorShader.bind();
	m_cursorShader.setUniformMat4f("u_viewMat", m_camera.getViewMatrix());
	drawScene();
	m_cursorShader.bind();
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
	if (!m_cubesMap.isPositionInsideWorld(ray.origin)) {
		float t = CubeMaths::IntersectionRayWorldborder(ray);
		if (t < std::numeric_limits<float>::infinity())
			ray.origin += (t + 0.01f) * ray.direction;
		else
			return;
	}
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

void App::ImGui_DebugWindow() {
	ImGui::Begin("Debug");
		ImGui::Checkbox("Show Demo Window", &m_bShowImGUIDemoWindow);
		ImGui::Text("Application average %.1f FPS", ImGui::GetIO().Framerate);
	ImGui::End();
}

void App::ImGui_Settings() {
	ImGui::Begin("Settings");
		ImGui::Text("Camera Control");
		ImGui::SliderFloat("Translation", &Settings::CAMERA_TRANSLATION_SPEED_PER_INCH, 0., 0.3);
		ImGui::SliderFloat("Rotation", &Settings::CAMERA_ROTATION_SPEED_IN_TURNS_PER_INCH, 0., 0.16);
		ImGui::SliderFloat("Zoom", &Settings::CAMERA_SCALE_RADIUS_PER_SCROLL, 0.01, 1.0);
	ImGui::End();
}

void App::ImGui_Camera() {
	ImGui::Begin("Camera");
	if (m_camera.ImGui_Sliders()) {
		Locate::materialsManager().updateMatrixUniform("u_projMat", m_camera.getProjMatrix());
		m_cursorShader.bind();
		m_cursorShader.setUniformMat4f("u_projMat", m_camera.getProjMatrix());
	}
	ImGui::End();
}

void App::ImGui_MainMenuBar() {
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::MenuItem("(dummy menu)", NULL, false, false);
			if (ImGui::MenuItem("New")) {}
			if (ImGui::MenuItem("Open", "Ctrl+O")) {}
			if (ImGui::BeginMenu("Open Recent"))
			{
				ImGui::MenuItem("fish_hat.c");
				ImGui::MenuItem("fish_hat.inl");
				ImGui::MenuItem("fish_hat.h");
				if (ImGui::BeginMenu("More.."))
				{
					ImGui::MenuItem("Hello");
					ImGui::MenuItem("Sailor");
					if (ImGui::BeginMenu("Recurse.."))
					{
						ImGui::EndMenu();
					}
					ImGui::EndMenu();
				}
				ImGui::EndMenu();
			}
			if (ImGui::MenuItem("Save", "Ctrl+S")) {}
			if (ImGui::MenuItem("Save As..")) {}
			ImGui::Separator();
			if (ImGui::BeginMenu("Options"))
			{
				static bool enabled = true;
				ImGui::MenuItem("Enabled", "", &enabled);
				ImGui::BeginChild("child", ImVec2(0, 60), true);
				for (int i = 0; i < 10; i++)
					ImGui::Text("Scrolling Text %d", i);
				ImGui::EndChild();
				static float f = 0.5f;
				static int n = 0;
				static bool b = true;
				ImGui::SliderFloat("Value", &f, 0.0f, 1.0f);
				ImGui::InputFloat("Input", &f, 0.1f);
				ImGui::Combo("Combo", &n, "Yes\0No\0Maybe\0\0");
				ImGui::Checkbox("Check", &b);
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Colors"))
			{
				float sz = ImGui::GetTextLineHeight();
				for (int i = 0; i < ImGuiCol_COUNT; i++)
				{
					const char* name = ImGui::GetStyleColorName((ImGuiCol)i);
					ImVec2 p = ImGui::GetCursorScreenPos();
					ImGui::GetWindowDrawList()->AddRectFilled(p, ImVec2(p.x + sz, p.y + sz), ImGui::GetColorU32((ImGuiCol)i));
					ImGui::Dummy(ImVec2(sz, sz));
					ImGui::SameLine();
					ImGui::MenuItem(name);
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Disabled", false)) // Disabled
			{
				IM_ASSERT(0);
			}
			if (ImGui::MenuItem("Checked", NULL, true)) {}
			if (ImGui::MenuItem("Quit", "Alt+F4")) {}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("New"))
		{
			if (ImGui::MenuItem("Shader Layer", "CTRL + F")) {
			}
			if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
			ImGui::Separator();
			if (ImGui::MenuItem("Cut", "CTRL+X")) {}
			if (ImGui::MenuItem("Copy", "CTRL+C")) {}
			if (ImGui::MenuItem("Paste", "CTRL+V")) {}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

void App::onEvent(const SDL_Event& e) {
	switch (e.type) {

	case SDL_MOUSEMOTION:
		if (!ImGui::GetIO().WantCaptureMouse)
			placeCursorJustBeforeHoveredCube();
		break;

	case SDL_MOUSEWHEEL:
		if (!ImGui::GetIO().WantCaptureMouse)
			m_camera.onWheelScroll(e.wheel.y);
		break;

	case SDL_MOUSEBUTTONDOWN:
		if (!ImGui::GetIO().WantCaptureMouse) {
			if (e.button.button == SDL_BUTTON_MIDDLE)
				m_camera.onWheelDown();
			else if (e.button.button == SDL_BUTTON_LEFT) {
				Locate::history(HistoryType::Cubes).beginUndoGroup();
					m_cubesMap.addCube(m_cursor.getPosition());
				Locate::history(HistoryType::Cubes).endUndoGroup();
				placeCursorJustBeforeHoveredCube();
			}
			else {
				Locate::history(HistoryType::Cubes).beginUndoGroup();
					m_cubesMap.removeCube(m_cursor.getPosition());
				Locate::history(HistoryType::Cubes).endUndoGroup();
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
			m_camera.mustRecomputeProjectionMatrix();
			Locate::materialsManager().updateMatrixUniform("u_projMat", m_camera.getProjMatrix());
			m_cursorShader.bind();
			m_cursorShader.setUniformMat4f("u_projMat", m_camera.getProjMatrix());
			break;
		}
		break;

	case SDL_QUIT:
		exit();
		break;

	default:
		break;
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
	handleSDLevents();
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

void App::handleSDLevents() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		ImGui_ImplSDL2_ProcessEvent(&e);
		onEvent(e);
	}
}