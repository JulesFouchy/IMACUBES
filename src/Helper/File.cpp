#include "File.hpp"

#include <sys/stat.h>

bool MyFile::Exists(const std::string& filepath) {
	struct stat buffer;
	return (stat(filepath.c_str(), &buffer) == 0);
}