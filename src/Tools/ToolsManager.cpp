#include "ToolsManager.hpp"

#include "Tool_MinecraftLike.hpp"
#include "Tool_Sphere.hpp"

#include <imgui/imgui.h>

ToolsManager::ToolsManager() {
	setTool<Tool_MinecraftLike>();
}

void ToolsManager::ImGui_SelectTool() {
	const char* listbox_items[] = { "Minecraft", "Sphere" };
	static int listbox_item_current = 0;
	ImGui::PushID((int)&m_activeTool);
	if (ImGui::ListBox("", &listbox_item_current, listbox_items, IM_ARRAYSIZE(listbox_items))) {
		switch (listbox_item_current)
		{
		case 0:
			setTool<Tool_MinecraftLike>();
			break;
		case 1:
			setTool<Tool_Sphere>();
			break;
		default:
			break;
		}
	}
	ImGui::PopID();
}