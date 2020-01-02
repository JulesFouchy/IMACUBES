#include "App.hpp"

#include "UI/Settings.hpp"
#include "Locator/Locate.hpp"

#include "imgui/misc/cpp/imgui_stdlib.h"

void App::ImGui_DebugWindow() {
	ImGui::Begin("Debug");
	ImGui::Checkbox("Show Demo Window", &m_bShowImGUIDemoWindow);
	ImGui::Text("Application average %.1f FPS", ImGui::GetIO().Framerate);
	ImGui::ColorPicker3("Background color", (float*)&m_clearColor);
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
		onProjMatrixChange();
	}
	if (ImGui::BeginPopupContextItem("fov reset"))
	{
		if (ImGui::Selectable("Reset")) {
			m_camera.resetFieldOfView();
			onProjMatrixChange();
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
			ImGui::Checkbox("Show cursor through cubes", &Settings::SHOW_CURSOR_THROUGH_CUBES);
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

void App::ImGui_RightSideWindow() {
	ImGuiWindowFlags flags =
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoTitleBar;
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
	ImGui::Begin("RightSideWindow", NULL, flags);

	ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
	if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
	{
		if (ImGui::BeginTabItem("Materials"))
		{
			Locate::materialsManager().ImGui_AddMaterialToSelectedShaderButton(); ImGui::SameLine();
			Locate::materialsManager().ImGui_AddShaderButton();
			Locate::materialsManager().ImGui_ListOfShadersAndMaterials();
			ImGui::EndTabItem();


			ImGui::BeginChild("Selected item", ImVec2(ImGui::GetWindowContentRegionWidth(), ImGui::GetWindowHeight() * 0.60));
			Locate::materialsManager().ImGui_SelectedMaterialsParameters();
			ImGui::EndChild();
		}
		if (ImGui::BeginTabItem("Lights"))
		{
			m_lightsManager.ImGui_AddLightOfSelectedTypeButton();
			ImGui::BeginChild("Items selection", ImVec2(ImGui::GetWindowContentRegionWidth(), ImGui::GetWindowHeight() * 0.30));
			m_lightsManager.ImGui_LightsList();
			ImGui::EndChild();
			ImGui::EndTabItem();

			ImGui::InputText("", m_lightsManager.selectedLight()->getNamePtr());
			ImGui::BeginChild("Selected item", ImVec2(ImGui::GetWindowContentRegionWidth(), ImGui::GetWindowHeight() * 0.60));
			m_lightsManager.ImGui_SelectedLightSliders();
			ImGui::EndChild();
		}
		ImGui::EndTabBar();
	}
	ImGui::PopStyleVar();
	ImGui::SetWindowSize(ImVec2(ImGui::GetWindowWidth(), m_renderer.GetHeight() - 18));
	ImGui::SetWindowPos(ImVec2(m_renderer.GetWidth() - ImGui::GetWindowWidth(), 18), true);
	ImGui::End();
	ImGui::PopStyleVar();
}