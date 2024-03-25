#pragma once

#include <memory>
#include "Tool.hpp"

class ToolsManager {
public:
    ToolsManager();
    ~ToolsManager() = default;

    inline Tool& tool() { return *m_activeTool; }

    void ImGui_SelectTool();

    template<typename T>
    inline void setTool()
    {
        m_activeTool = std::make_unique<T>();
    }

private:
    std::unique_ptr<Tool> m_activeTool;
};