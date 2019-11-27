#include "UniformFactory.hpp"

#include "Helper/String.hpp"

#include "Types/OpenGLTypes.hpp"

#include "glm/glm.hpp"

namespace UniformFactory {
	Uniform* FromShaderLine(GLuint shaderID, const std::string& line) {
		// Parse uniform
		size_t posBeginUniform = line.find("uniform");
		// Get type
		size_t posBeginType = MyString::BeginningOfNextWord(line, MyString::EndOfNextWord(line, posBeginUniform) + 1);
		size_t posEndType = MyString::EndOfNextWord(line, posBeginType);
		OpenGLType type = GLType::FromString(line.substr(posBeginType, posEndType - posBeginType));
		switch (type)
		{
		case Int:
			return ReadNameAndValuesAndCreateUniformOfType<int>(shaderID, line, posEndType);
			break;
		case Float:
			return ReadNameAndValuesAndCreateUniformOfType<float>(shaderID, line, posEndType);
			break;
		case Vec2:
			return ReadNameAndValuesAndCreateUniformOfType<glm::vec2>(shaderID, line, posEndType);
			break;
		case Vec3:
			return ReadNameAndValuesAndCreateUniformOfType<glm::vec3>(shaderID, line, posEndType);
			break;
		case Vec4:
			return ReadNameAndValuesAndCreateUniformOfType<glm::vec4>(shaderID, line, posEndType);
			break;
		default:
			spdlog::warn("[UniformFactory::FromShaderLine] Unknown OpenGL type : {}", type);
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