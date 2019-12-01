#include "UniformFactory.hpp"

#include "Helper/String.hpp"

#include "OpenGL/OpenGLTypes.hpp"

#include "glm/glm.hpp"

namespace UniformFactory {
	Uniform* FromShaderLine(int shaderIndex, const std::string& line) {
		// Get type
		size_t currentPos = 0;
		OpenGLType type = GLType::FromString(MyString::GetNextWord(line, &currentPos));
		switch (type)
		{
		case OpenGLType::Int:
			return ReadNameAndValuesAndCreateUniformOfType<int>(shaderIndex, line, currentPos);
			break;
		case OpenGLType::Float:
			return ReadNameAndValuesAndCreateUniformOfType<float>(shaderIndex, line, currentPos);
			break;
		case OpenGLType::Vec2:
			return ReadNameAndValuesAndCreateUniformOfType<glm::vec2>(shaderIndex, line, currentPos);
			break;
		case OpenGLType::Vec3:
			return ReadNameAndValuesAndCreateUniformOfType<glm::vec3>(shaderIndex, line, currentPos);
			break;
		case OpenGLType::Vec4:
			return ReadNameAndValuesAndCreateUniformOfType<glm::vec4>(shaderIndex, line, currentPos);
			break;
		default:
			spdlog::warn("[UniformFactory::FromShaderLine] Unknown OpenGL type : {}", (int)type);
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