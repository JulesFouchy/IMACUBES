#include "ToolsManager.hpp"

#include "Tool_MinecraftLike.hpp"
#include "Tool_Sphere.hpp"

ToolsManager::ToolsManager() {
	setTool<Tool_Sphere>();
}