#include "App.hpp"

#include <imgui.h>
#include <imgui/imgui_impl_sdl.h>
#include <imgui/imgui_impl_opengl3.h>
#include <glm/glm.hpp>

#include "Debugging/Log.hpp"
#include "Debugging/ImGuiLog.hpp"
#include "Debugging/gl-exception.h"

#include "Helper/File.hpp"
#include "UI/Input.hpp"
#include "Locator/Locate.hpp"
#include "Material/MaterialsManager.hpp"
#include "CubeMaths/CubeMaths.hpp"

#include <algorithm>


App::App(SDL_Window* window)
	: m_renderer(window),
	  m_cubesMap(51, 51, 51), m_camera(glm::vec3(0.0f)),
	  m_lightsManager(),
	  m_bShowImGUIDemoWindow(false),
	  m_bAddTheSelectedSomething(false),
	  m_window(window), m_running(true)
{
	spdlog::info("Root directory is {}", MyFile::rootDir);
}

void App::onInit() {
	// ----------------PLAYGROUND!------------------

	m_renderer.initAfterApp();
	m_camera.initAfterApp();
	m_cursorShaderLID = m_shaders.LoadShader(MyFile::rootDir+"/res/shaders/_cursor.vert", MyFile::rootDir + "/res/shaders/_cursor.frag");
	m_renderer.cameraUniforms().addSubscriber(m_cursorShaderLID);

	Locate::materialsManager().addShader(MyFile::rootDir+"/res/shaders/_geometryPass.vert", MyFile::rootDir+"/res/shaders/FlatColor.frag");
	Locate::materialsManager().addShader(MyFile::rootDir+"/res/shaders/_geometryPass.vert", MyFile::rootDir+"/res/shaders/FlatColorPlusBorder.frag");
	//Locate::materialsManager().addShader(MyFile::rootDir+"/res/shaders/_geometryPass.vert", MyFile::rootDir+"/res/shaders/testShader.frag");
	Locate::materialsManager().setSelectedMaterial(0, 0);

	onViewMatrixChange();
	onProjMatrixChange();

	Locate::history(HistoryType::Cubes).beginUndoGroup();
	for (int x = -m_cubesMap.width()*0.3; x < m_cubesMap.width()*0.3; ++x) {
		for (int z = -m_cubesMap.depth()*0.3; z < m_cubesMap.depth()*0.3; ++z) {
			for (int y = std::max(-(int)m_cubesMap.height()/2, -5); y < 0; ++y) {
				m_cubesMap.addCube(glm::ivec3(x, y, z));
			}
		}
	}
	Locate::history(HistoryType::Cubes).endUndoGroup();
}


void App::onLoopIteration() {
	// ImGui windows
	ImGui_DebugWindow();
	if (m_bShowImGUIDemoWindow) // Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		ImGui::ShowDemoWindow(&m_bShowImGUIDemoWindow);
	ImGui_MainMenuBar();
	ImGui_RightSideWindow();


	// ----------------PLAYGROUND!------------------
	m_camera.update(1.0f / 60.0f);
	m_lightsManager.setUniforms(m_renderer.lightUniforms());
	onViewMatrixChange();
	m_renderer.drawScene();
	m_renderer.m_gBuffer.copyDepthTo(0);
	m_shaders[m_cursorShaderLID].bind();
	m_cursor.draw();
	m_toolrbf.showGUI();
	m_saveViewWindow.Show_IfOpen();
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
	while (m_cubesMap.isID3Dvalid(iPos) && !m_cubesMap.cubeExists(iPos)) {
		float t = CubeMaths::IntersectionRayCube_WROIC(ray, iPos);
		ray.origin += (t + 0.01f) * ray.direction;
		iPos = CubeMaths::CubeContaining(ray.origin);
		if (m_cubesMap.isID3Dvalid(iPos) && !m_cubesMap.cubeExists(iPos))
			prevIpos = iPos;
	}
	if (m_cubesMap.isID3Dvalid(prevIpos)) {
		m_cursor.setCubeJustBeforePosition(prevIpos);
	}
	if (m_cubesMap.isID3Dvalid(iPos)) {
		m_cursor.setPosition(iPos);
	}
	else {
		if (m_cubesMap.isID3Dvalid(prevIpos)) {
			m_cursor.setPosition(prevIpos);
		}
	}
}

void App::onViewMatrixChange(){
	m_renderer.cameraUniforms().setUniform<glm::mat4>("u_ViewMat", m_camera.getViewMatrix());
	m_renderer.SSAOmatrixUniforms().setUniform<glm::mat4>("u_ViewMat", m_camera.getViewMatrix());
	m_renderer.SSAOmatrixUniforms().setUniform<glm::mat4>("u_NormalMat", m_camera.getNormalMatrix());
	m_renderer.lightUniforms().setUniform<glm::vec3>("u_CamPosInWorld", m_camera.getPosition());
}
void App::onProjMatrixChange() {
	m_renderer.cameraUniforms().setUniform<glm::mat4>("u_ProjMat", m_camera.getProjMatrix());
	m_renderer.SSAOmatrixUniforms().setUniform<glm::mat4>("u_ProjMat", m_camera.getProjMatrix());
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

				//m_toolrbf.onLeftClick(m_cursor);
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
					Locate::materialsManager().Shaders()[Locate::materialsManager().SelectedMaterialLocation().shaderID].reloadShader();
					m_renderer.cameraUniforms().sendUniformsTo(Locate::materialsManager().Shaders()[Locate::materialsManager().SelectedMaterialLocation().shaderID].shaderLID());
				}
				if (e.key.keysym.sym == 'z') {
					m_cursor.translate(glm::ivec3(0, 0, -1));
				}
				else if (e.key.keysym.sym == 's') {
					m_cursor.translate(glm::ivec3(0, 0, 1));
				}
				else if (e.key.keysym.sym == 'q') {
					m_cursor.translate(glm::ivec3(-1, 0, 0));
				}
				else if (e.key.keysym.sym == 'd') {
					m_cursor.translate(glm::ivec3(1, 0, 0));
				}
				else if (e.key.keysym.sym == 'w') {
					m_cursor.translate(glm::ivec3(0, -1, 0));
				}
				else if (e.key.keysym.sym == 'x') {
					m_cursor.translate(glm::ivec3(0, 1, 0));
				}
				else if (e.key.keysym.sym == 'c') {
					m_camera.setLookedAtPoint(m_cursor.getPosition());
					onViewMatrixChange();
				}
				else if (e.key.keysym.sym == 'p') {
					m_lightsManager.trySetSelectedPointLightPosition(m_cursor.getCubeJustBeforePosition());
				}
				else if (e.key.keysym.sym == ' ') {
					const MaterialLocation& matLoc = m_cubesMap[m_cursor.getPosition()];
					if (matLoc.isValid())
						m_cubesMap.materialsManager().setSelectedMaterial(matLoc.shaderID, matLoc.materialID);
				}
				else if (e.key.keysym.sym == '+' || e.key.keysym.sym == '=') {
					m_bAddTheSelectedSomething = true;
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
			m_renderer.onWindowResize();
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
	if (m_instance == nullptr)
		spdlog::error("[App::Initialize] unable to allocate enough memory !");
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