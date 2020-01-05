#pragma once

#include "Tool.hpp"

#include <memory>

class ToolsManager {
public:
	ToolsManager();
	~ToolsManager() = default;

	inline Tool& tool() { return *m_activeTool; }

	template <typename T>
	inline void setTool() { m_activeTool = std::make_unique<T>(); }

private:
	std::unique_ptr<Tool> m_activeTool;
};