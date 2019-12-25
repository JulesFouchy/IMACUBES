#include "App.hpp"

#include <imgui.h>
#include <imgui/imgui_impl_sdl.h>
#include <imgui/imgui_impl_opengl3.h>
#include <glm/glm.hpp>

#include "Debugging/Log.hpp"
#include "Debugging/ImGuiLog.hpp"
#include "Debugging/gl-exception.h"

#include "Helper/Display.hpp"
#include "Helper/File.hpp"
#include "UI/Input.hpp"
#include "Locator/Locate.hpp"
#include "Material/MaterialsManager.hpp"
#include "CubeMaths/CubeMaths.hpp"

#include <algorithm>


App::App(SDL_Window* window)
	: m_cubesMap(100, 100, 100), m_cursor(), m_camera(glm::vec3(m_cubesMap.width()/2, m_cubesMap.height()/2, m_cubesMap.depth()/2)),
	  m_clearColor(0.0f, 0.066f, 0.18f), m_ambiantLight("Ambiant Light 1"), m_pointLight(glm::vec3(m_cubesMap.width()/2, m_cubesMap.height()/2, m_cubesMap.depth()/2), "PointLight 1"), m_directionalLight(glm::vec3(-49., -173, 167), "Directional Light 1"),
	  m_bShowImGUIDemoWindow(false),
	  m_window(window), m_running(true)
{
	spdlog::info("Root directory is {}", MyFile::rootDir);
}

void App::onInit() {
	// ----------------PLAYGROUND!------------------

	m_cursorShaderLID = m_shaders.LoadShader(MyFile::rootDir+"/res/shaders/_cursor.vert", MyFile::rootDir + "/res/shaders/_cursor.frag");
	m_cameraUniforms.addSubscriber(m_cursorShaderLID);

	m_cursor = Cursor(m_cubesMap.width()/2, m_cubesMap.height()/2, m_cubesMap.depth()/2);
	Locate::materialsManager().addShader(MyFile::rootDir+"/res/shaders/_default.vert", MyFile::rootDir+"/res/shaders/FlatColor.frag");
	Locate::materialsManager().addShader(MyFile::rootDir+"/res/shaders/_default.vert", MyFile::rootDir+"/res/shaders/FlatColorPlusBorder.frag");
	Locate::materialsManager().addShader(MyFile::rootDir+"/res/shaders/_default.vert", MyFile::rootDir+"/res/shaders/testShader.frag");
	Locate::materialsManager().SetSelectedMaterial(1, 0);

	onViewMatrixChange();
	onProjMatrixChange();

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
	//_ImGui_Settings();
	//_ImGui_Camera();
	ImGui::Begin("Ambiant");
	m_ambiantLight.ImGui_Sliders();
	ImGui::End();	
	ImGui::Begin("Point");
	m_pointLight.ImGui_Sliders();
	ImGui::End();
	ImGui::Begin("Directional");
	m_directionalLight.ImGui_Sliders();
	ImGui::End();
	m_ambiantLight.setUniforms("u_ambiant", m_lightUniforms);
	m_pointLight.setUniforms("u_point", m_lightUniforms);
	m_directionalLight.setUniforms("u_directional", m_lightUniforms);
	if (m_bShowImGUIDemoWindow) // Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		ImGui::ShowDemoWindow(&m_bShowImGUIDemoWindow);
	ImGui_MainMenuBar();

	// ----------------PLAYGROUND!------------------
	m_camera.update(1.0f / 60.0f);
	onViewMatrixChange();
	drawScene();
	m_shaders[m_cursorShaderLID].bind();
	m_cursor.draw();
	Locate::materialsManager().ImGui_Menu();
	m_saveViewWindow.Show_IfOpen();
}


void App::drawScene() {
	GLCall(glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	Locate::materialsManager().draw();
}

void App::placeCursorAtHoveredCube(){
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
		m_cursor.setCubeJustBeforePosition(prevIpos);
	}
	if (m_cubesMap.isIDvalid(iPos)) {
		m_cursor.setPosition(iPos);
	}
}

void App::onViewMatrixChange(){
	m_cameraUniforms.setUniform<glm::mat4>("u_viewMat", m_camera.getViewMatrix());
}
void App::onProjMatrixChange() {
	m_cameraUniforms.setUniform<glm::mat4>("u_projMat", m_camera.getProjMatrix());
}

void App::onEvent(const SDL_Event& e) {
	switch (e.type) {

	case SDL_MOUSEMOTION:
		if (!ImGui::GetIO().WantCaptureMouse)
			placeCursorAtHoveredCube();
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
					m_cubesMap.addCube(m_cursor.getCubeJustBeforePosition());
				Locate::history(HistoryType::Cubes).endUndoGroup();
				placeCursorAtHoveredCube();
			}
			else {
				Locate::history(HistoryType::Cubes).beginUndoGroup();
					m_cubesMap.removeCube(m_cursor.getPosition());
				Locate::history(HistoryType::Cubes).endUndoGroup();
				placeCursorAtHoveredCube();
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
					m_cameraUniforms.setUniformsFor(Locate::materialsManager().Shaders()[Locate::materialsManager().SelectedMaterial().shaderID].shaderLID());
					m_lightUniforms.setUniformsFor(Locate::materialsManager().Shaders()[Locate::materialsManager().SelectedMaterial().shaderID].shaderLID());
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
				else if (e.key.keysym.sym == 'c') {
					m_camera.setLookedAtPoint(m_cursor.getPosition());
					onViewMatrixChange();
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
			onProjMatrixChange();
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