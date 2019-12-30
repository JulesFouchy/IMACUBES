#include "UniformDescriptionFactory.hpp"

#include "Helper/String.hpp"

#include "OpenGL/OpenGLTypes.hpp"

#include "glm/glm.hpp"

namespace UniformDescriptionFactory {

	UniformDescription* FromShaderLine(const std::string& line, HistoryType historyType) {
		// Get type
		size_t currentPos = 0;
		OpenGLType type = GLType::FromString(MyString::GetNextWord(line, &currentPos));
		switch (type)
		{
		case OpenGLType::Int:
			return ReadNameAndValuesAndCreateUniformDescriptionOfType<int>(line, currentPos, historyType);
			break;
		case OpenGLType::Float:
			return ReadNameAndValuesAndCreateUniformDescriptionOfType<float>(line, currentPos, historyType);
			break;
		case OpenGLType::Vec2:
			return ReadNameAndValuesAndCreateUniformDescriptionOfType<glm::vec2>(line, currentPos, historyType);
			break;
		case OpenGLType::Vec3:
			return ReadNameAndValuesAndCreateUniformDescriptionOfType<glm::vec3>(line, currentPos, historyType);
			break;
		case OpenGLType::Vec4:
			return ReadNameAndValuesAndCreateUniformDescriptionOfType<glm::vec4>(line, currentPos, historyType);
			break;
		default:
			spdlog::warn("[UniformDescriptionFactory::FromShaderLine] Unknown OpenGL type : {}", (int)type);
			return nullptr;
			break;
		}
	}

	namespace {
		template <>
		int ReadValue<int>(const std::string& str, size_t* currentPosPtr) {
			return std::stoi(MyString::GetNextWord(str, currentPosPtr));
		}

		template <>
		float ReadValue<float>(const std::string& str, size_t* currentPosPtr) {
			return std::stof(MyString::GetNextWord(str, currentPosPtr));
		}

		template <>
		glm::vec2 ReadValue<glm::vec2>(const std::string& str, size_t* currentPosPtr) {
			float x = std::stof(MyString::GetNextWord(str, currentPosPtr));
			float y = std::stof(MyString::GetNextWord(str, currentPosPtr));
			return glm::vec2(x, y);
		}

		template <>
		glm::vec3 ReadValue<glm::vec3>(const std::string& str, size_t* currentPosPtr) {
			float x = std::stof(MyString::GetNextWord(str, currentPosPtr));
			float y = std::stof(MyString::GetNextWord(str, currentPosPtr));
			float z = std::stof(MyString::GetNextWord(str, currentPosPtr));
			return glm::vec3(x, y, z);
		}

		template <>
		glm::vec4 ReadValue<glm::vec4>(const std::string& str, size_t* currentPosPtr) {
			float x = std::stof(MyString::GetNextWord(str, currentPosPtr));
			float y = std::stof(MyString::GetNextWord(str, currentPosPtr));
			float z = std::stof(MyString::GetNextWord(str, currentPosPtr));
			float w = std::stof(MyString::GetNextWord(str, currentPosPtr));
			return glm::vec4(x, y, z, w);
		}
	}
}