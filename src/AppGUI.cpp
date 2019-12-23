#include "App.hpp"

#include "UI/Settings.hpp"
#include "Locator/Locate.hpp"

void App::ImGui_DebugWindow() {
	ImGui::Begin("Debug");
	ImGui::Checkbox("Show Demo Window", &m_bShowImGUIDemoWindow);
	ImGui::Text("Application average %.1f FPS", ImGui::GetIO().Framerate);
	ImGui::End();
}

void App::_ImGui_CameraControls() {
	// Translation
	ImGui::SliderFloat("Translation", &Settings::CAMERA_TRANSLATION_SPEED_PER_INCH, 0., 0.3);
	if (ImGui::BeginPopupContextItem("translation reset"))
	{
		if (ImGui::Selectable("Reset")) Settings::CAMERA_TRANSLATION_SPEED_PER_INCH = Settings::DEFAULT_CAMERA_TRANSLATION_SPEED_PER_INCH;
		ImGui::EndPopup();
	}
	// Rotation
	ImGui::SliderFloat("Rotation", &Settings::CAMERA_ROTATION_SPEED_IN_TURNS_PER_INCH, 0., 0.16);
	if (ImGui::BeginPopupContextItem("rotation reset"))
	{
		if (ImGui::Selectable("Reset")) Settings::CAMERA_ROTATION_SPEED_IN_TURNS_PER_INCH = Settings::DEFAULT_CAMERA_ROTATION_SPEED_IN_TURNS_PER_INCH;
		ImGui::EndPopup();
	}
	// Scale
	ImGui::SliderFloat("Zoom", &Settings::CAMERA_SCALE_RADIUS_PER_SCROLL, 0.01, 1.0);
	if (ImGui::BeginPopupContextItem("scale reset"))
	{
		if (ImGui::Selectable("Reset")) Settings::CAMERA_SCALE_RADIUS_PER_SCROLL = Settings::DEFAULT_CAMERA_SCALE_RADIUS_PER_SCROLL;
		ImGui::EndPopup();
	}
}

void App::_ImGui_CameraView() {
	// Field of View
	if (m_camera.ImGui_View()) {
		Locate::materialsManager().updateMatrixUniform("u_projMat", m_camera.getProjMatrix());
		m_cursorShader.bind();
		m_cursorShader.setUniformMat4f("u_projMat", m_camera.getProjMatrix());
	}
	if (ImGui::BeginPopupContextItem("fov reset"))
	{
		if (ImGui::Selectable("Reset")) {
			m_camera.resetFieldOfView();
			Locate::materialsManager().updateMatrixUniform("u_projMat", m_camera.getProjMatrix());
			m_cursorShader.bind();
			m_cursorShader.setUniformMat4f("u_projMat", m_camera.getProjMatrix());
		}
		ImGui::EndPopup();
	}
}

void App::ImGui_MainMenuBar() {
	if (ImGui::BeginMainMenuBar()) {
		// Settings
		if (ImGui::BeginMenu("Settings")) {
			if (ImGui::BeginMenu("Camera sensitivity")) {
				_ImGui_CameraControls();
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		// Histories
		if (ImGui::BeginMenu("Histories")) {
			if (ImGui::BeginMenu("Active history")) {
				m_histories._ImGui_ActiveHistory();
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		// Camera
		if (ImGui::BeginMenu("Camera")) {
			if (ImGui::BeginMenu("Transform")) {
				m_camera.ImGui_Transform();
				ImGui::EndMenu();
			}
			if (ImGui::BeginPopupContextItem("camera transform reset"))
			{
				if (ImGui::Selectable("Reset")) {
					m_camera.resetTransform();
				}
				ImGui::EndPopup();
			}
			if (ImGui::BeginMenu("View")) {
				_ImGui_CameraView();
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		//
		ImGui::EndMainMenuBar();
	}
}