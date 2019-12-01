#pragma once

#include <string>

namespace MyString {
	size_t BeginningOfNextWord(const std::string& myString, size_t beginPos);
	size_t EndOfNextWord(const std::string& myString, size_t beginPos);
	std::string GetNextWord(const std::string& myString, size_t* currentPosition);
	void ReplaceAll(std::string& str, const std::string& from, const std::string& to);
	std::string GetFileExtension(const std::string& myString);
	std::string RemoveFolderHierarchy(const std::string& myString);
	std::string RemoveFileExtension(const std::string& myString);
}