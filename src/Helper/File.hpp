#pragma once

#include <filesystem>
#include <string>

namespace MyFile {
bool        Exists(const std::string& filepath);
std::string GetFullPath(const std::string& filepath);

const std::string rootDir = std::filesystem::current_path().string();
} // namespace MyFile