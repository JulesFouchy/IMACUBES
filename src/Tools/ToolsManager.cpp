#include "ToolsManager.hpp"

#include "Tool_MinecraftLike.hpp"
#include "Tool_Cube.hpp"
#include "Tool_BoxTwoCorners.hpp"
#include "Tool_Sphere.hpp"
#include "Tool_OvoidTwoCorners.hpp"
#include "Tool_RBF.hpp"

#include <imgui/imgui.h>

ToolsManager::ToolsManager() {
	setTool<Tool_MinecraftLike>();
}

void ToolsManager::ImGui_SelectTool() {
	const char* listbox_items[] = { "Minecraft", "Cube", "Box two corners", "Sphere", "Ovoid two corners", "Radial Basis Functions" };
	static int listbox_item_current = 0;
	ImGui::PushID((int)&m_activeTool);
	if (ImGui::ListBox("", &listbox_item_current, listbox_items, IM_ARRAYSIZE(listbox_items))) {
		switch (listbox_item_current)
		{
		case 0:
			setTool<Tool_MinecraftLike>();
			break;
		case 1:
			setTool<Tool_Cube>();
			break;
		case 2:
			setTool<Tool_BoxTwoCorners>();
			break;
		case 3:
			setTool<Tool_Sphere>();
			break;
		case 4:
			setTool<Tool_OvoidTwoCorners>();
			break;
		case 5:
			setTool<Tool_RBF>();
		default:
			break;
		}
	}
	ImGui::PopID();
}