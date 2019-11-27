#pragma once

#include "UniformConcrete.hpp"

namespace UniformFactory {
	// public :
	Uniform* FromString(GLuint shaderID, const std::string& line);

	// private :
	template <typename T>
	T ReadValue(const std::string& str, size_t* currentPosPtr);

	template <typename T>
	Uniform* ReadAndCreateUniformOfType(GLuint shaderID, const std::string& line, size_t posEndType) {
		// Get name
		size_t posBeginName = MyString::BeginningOfNextWord(line, posEndType);
		size_t posEndName = MyString::EndOfNextWord(line, posBeginName);
		std::string s_name = line.substr(posBeginName, posEndName - posBeginName);
		spdlog::info("found uniform {}", s_name);
		// Get options
		T initialValue = T(0);
		T minValue = T(0);
		T maxValue = T(1);
		size_t posBeginComment = line.find("//");
		if (posBeginComment != std::string::npos) {
			size_t currentPos = MyString::BeginningOfNextWord(line, MyString::EndOfNextWord(line, posBeginComment) + 1);
			while (currentPos < line.size()) {
				std::string arg = MyString::GetNextWord(line, &currentPos);
				spdlog::info("|" + arg + "|");
				if (arg == "default") {
					initialValue = ReadValue<T>(line, &currentPos);
				}
				else if (arg == "min") {
					minValue = ReadValue<T>(line, &currentPos);
				}
				else if (arg == "max") {
					maxValue = ReadValue<T>(line, &currentPos);
				}
				else {
					spdlog::warn("[UniformFactory::ReadAndCreateUniformOfType] Unknown argument : {}", arg);
				}
			}
		}
		// Return uniform
		return new UniformConcrete<T>(shaderID, s_name, initialValue, minValue, maxValue);
	}
}