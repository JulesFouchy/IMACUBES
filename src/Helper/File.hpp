#pragma once

#include <string>

namespace MyFile {
	bool Exists(const std::string& filepath);
	std::string GetFullPath(const std::string& filepath);
}