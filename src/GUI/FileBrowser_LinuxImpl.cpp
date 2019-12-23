#ifdef  __linux__

#include "FileBrowser.hpp"

#include "Debugging/Log.hpp"

std::string FileBrowser::openfilename(const char* filter) {
	spdlog::warn("Sorry, file explorer not implemented for Linux yet ! ");
}

std::string FileBrowser::savefilename(const char* filter) {
	spdlog::warn("Sorry, file explorer not implemented for Linux yet ! ");
}

#endif //  __linux__
