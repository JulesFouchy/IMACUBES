#include "ImGuiLog.hpp"
#include <imgui/imgui.h>

void ImGuiLog::Log(const std::string& name, glm::mat4 mat)
{
    ImGui::Begin(name.c_str());
    std::string str = std::to_string(mat[0][0]) + " " + std::to_string(mat[1][0]) + " " + std::to_string(mat[2][0]) + " " + std::to_string(mat[3][0]) + "\n"
                      + std::to_string(mat[0][1]) + " " + std::to_string(mat[1][1]) + " " + std::to_string(mat[2][1]) + " " + std::to_string(mat[3][1]) + "\n"
                      + std::to_string(mat[0][2]) + " " + std::to_string(mat[1][2]) + " " + std::to_string(mat[2][2]) + " " + std::to_string(mat[3][2]) + "\n"
                      + std::to_string(mat[0][3]) + " " + std::to_string(mat[1][3]) + " " + std::to_string(mat[2][3]) + " " + std::to_string(mat[3][3]);
    ImGui::Text(str.c_str());
    ImGui::End();
}