#include "File.hpp"

#include <sys/stat.h>
#include <filesystem>

bool MyFile::Exists(const std::string& filepath) {
	struct stat buffer;
	return (stat(filepath.c_str(), &buffer) == 0);
}

std::string MyFile::GetFullPath(const std::string& filepath) {
	namespace fs = std::filesystem;
	return fs::absolute(filepath).string();
}