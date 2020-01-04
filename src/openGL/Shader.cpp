#include "Shader.hpp"

#include <glad/glad.h>
#include "Debugging/gl-exception.h"

#include <fstream>
#include <iostream>

#include "Helper/String.hpp"
#include "Helper/File.hpp"

#include "Debugging/Log.hpp"

Shader::Shader(const std::string& vertexShaderFilepath, const std::string& fragmentShaderFilepath, bool compileShader, const std::vector<std::string>& lookForInFS, const std::vector<std::string>& replaceWithInFS, const std::vector<std::string>& lookForInVS, const std::vector<std::string>& replaceWithInVS)
	: m_shaderId(-1), m_vsID(-1), m_fsID(-1), m_vertexShaderFilepath(MyFile::GetFullPath(vertexShaderFilepath)), m_fragmentShaderFilepath(MyFile::GetFullPath(fragmentShaderFilepath)),
	  m_bCreatedSuccessfully(true)
{
	if (compileShader) {
		compile(lookForInFS, replaceWithInFS, lookForInVS, replaceWithInVS);
	}
}

//Shader::Shader(const Shader& other)
//	: m_shaderId(-1), m_vsID(other.m_vsID), m_fsID(other.m_fsID), m_vertexShaderFilepath(other.m_vertexShaderFilepath), m_fragmentShaderFilepath(other.m_fragmentShaderFilepath),
//	m_bCreatedSuccessfully(true)
//{
//	spdlog::error("Shader copy constructor is slightly broken !!");
//	//FIXME compile must take into account the #define !
//	compile();
//}

Shader::Shader(Shader&& other) noexcept
	: m_shaderId(other.m_shaderId), m_vsID(other.m_vsID), m_fsID(other.m_fsID), m_vertexShaderFilepath(other.m_vertexShaderFilepath), m_fragmentShaderFilepath(other.m_fragmentShaderFilepath),
	m_bCreatedSuccessfully(true) 
{
	other.m_shaderId = -1;
}

Shader::~Shader() {
	glDeleteProgram(m_shaderId);
}

void Shader::bind() const {
	glUseProgram(m_shaderId);
}


void Shader::compile(const std::vector<std::string>& lookForInFS, const std::vector<std::string>& replaceWithInFS, const std::vector<std::string>& lookForInVS, const std::vector<std::string>& replaceWithInVS) {
	spdlog::info("[Compiling Shader] " + m_vertexShaderFilepath + " & " + m_fragmentShaderFilepath);
	if (m_shaderId == -1) {
		m_shaderId = glCreateProgram();
	}
	else {
		(glDetachShader(m_shaderId, m_vsID));
		(glDetachShader(m_shaderId, m_fsID));
	}
	m_vsID = compileShader(GL_VERTEX_SHADER, parseFile(m_vertexShaderFilepath, lookForInVS, replaceWithInVS));
	m_fsID = compileShader(GL_FRAGMENT_SHADER, parseFile(m_fragmentShaderFilepath, lookForInFS, replaceWithInFS));

	(glAttachShader(m_shaderId, m_vsID));
	(glAttachShader(m_shaderId, m_fsID));
	(glLinkProgram(m_shaderId));
	(glValidateProgram(m_shaderId));

	GLCall(glDeleteShader(m_vsID));
	GLCall(glDeleteShader(m_fsID));

	m_UniformLocationCache = std::unordered_map<std::string, int>(); // reset uniform locations
	Log::separationLine();
}

void Shader::compile(const std::string& lookForInFS , const std::string& replaceWithInFS , const std::string& lookForInVS, const std::string& replaceWithInVS) {
	std::vector<std::string> vectLookForInFS     = { lookForInFS };
	std::vector<std::string> vectReplaceWithInFS = { replaceWithInFS };
	std::vector<std::string> vectLookForInVS     = { lookForInVS };
	std::vector<std::string> vectReplaceWithInVS = { replaceWithInVS };
	compile(vectLookForInFS, vectReplaceWithInFS, vectLookForInVS, vectReplaceWithInVS);
}

//Uniforms

int Shader::getUniformLocation(std::string uniformName) {
	if (m_UniformLocationCache.find(uniformName) != m_UniformLocationCache.end()) {
		return m_UniformLocationCache[uniformName];
	}

	int location = glGetUniformLocation(m_shaderId, uniformName.c_str());
	if (location == -1) {
		//spdlog::warn("[Shader::getUniformLocation] uniform '{}' doesn't exist or it was removed during compilation because it wasn't used", uniformName);
		return -1;
	}
	m_UniformLocationCache[uniformName] = location;
	return location;
}

void Shader::setUniform1i(const std::string& uniformName, int v) {
	glUniform1i(getUniformLocation(uniformName), v);
}
void Shader::setUniform1f(const std::string& uniformName, float v) {
	glUniform1f(getUniformLocation(uniformName), v);
}
void Shader::setUniform2f(const std::string& uniformName, const glm::vec2& v) {
	glUniform2f(getUniformLocation(uniformName), v.x, v.y);
}
void Shader::setUniform3f(const std::string& uniformName, const glm::vec3& v) {
	glUniform3f(getUniformLocation(uniformName), v.x, v.y, v.z);
}
void Shader::setUniform4f(const std::string& uniformName, const glm::vec4& v) {
	glUniform4f(getUniformLocation(uniformName), v.x, v.y, v.z, v.w);
}
void Shader::setUniformMat4f(const std::string& uniformName, const glm::mat4& mat) {
	glUniformMatrix4fv(getUniformLocation(uniformName), 1, GL_FALSE, &mat[0][0]);
}

/* Utilities to open files and compile shaders */

std::string Shader::parseFile(const std::string& filepath, const std::vector<std::string>& vectLookFor, const std::vector<std::string>& vectReplaceWith) {
	std::ifstream stream(filepath);
	if (!stream.is_open()) {
		spdlog::warn("[Shader::parseFile] Failed to open file |{}|", filepath);
		m_bCreatedSuccessfully = false;
		return "";
	}

	// Info
	for (int k = 0; k < vectLookFor.size(); ++k)
		spdlog::info("Replacing '{}' with '{}'", vectLookFor[k], vectReplaceWith[k]);
	//

	std::string str = "";
	std::string line = "";
	while (getline(stream, line)) {
		size_t commPos = line.find("//");
		// Look for something to replace
		for( int k = 0; k < vectLookFor.size(); ++k)
			MyString::ReplaceAll(line, vectLookFor[k], vectReplaceWith[k]);
		// Look for '#include'
		size_t includePos = line.find("#include");
		if (includePos != std::string::npos && includePos < commPos) {
			size_t pos = 0;
			MyString::GetNextWord(line, &pos);
			std::string filepathToInclude = MyString::GetNextWord(line, &pos, " ,;()|\t\"");
			filepathToInclude = MyFile::rootDir + "/res/shaders/" + filepathToInclude; // make absolute path
			spdlog::info("Including |{}|", filepathToInclude);
			str += parseFile(filepathToInclude, vectLookFor, vectReplaceWith);
		}
		// Simply add line
		else {
			str += line + '\n';
		}
	}
	stream.close();
	return str;
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);
	//Debug
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		m_bCreatedSuccessfully = false;
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		spdlog::warn("Failed to compile {} {}", (type == GL_FRAGMENT_SHADER ? "fragment" : "vertex") , "shader");
		spdlog::warn(message);
		glDeleteShader(id);
		return 0;
	}

	return id;
}
