#include "ShaderAndItsMaterials.hpp"

#include <fstream>
#include "Helper/String.hpp"

#include "Debugging/Log.hpp"
#include "OpenGL/OpenGLTypes.hpp"
#include "OpenGL/Uniform/UniformFactory.hpp"

ShaderAndItsMaterials::ShaderAndItsMaterials(const std::string& vertexFilepath, const std::string& fragmentFilepath)
	: m_shader(vertexFilepath, fragmentFilepath), m_cubes(0,0,0), m_name(MyString::RemoveFolderHierarchy(fragmentFilepath))
{
	m_uniforms.addStruct();
	parseShader(fragmentFilepath);
	m_uniforms.addStruct();
}

ShaderAndItsMaterials::~ShaderAndItsMaterials() {

}

void ShaderAndItsMaterials::draw() {
	m_shader.bind();
	setUniforms();
	m_cubes.draw();
}

void ShaderAndItsMaterials::setUniforms() {
	m_uniforms.setUniforms();
}


void ShaderAndItsMaterials::parseShader(const std::string& fragmentFilepath) {
	std::ifstream file(fragmentFilepath);
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			// Parse uniform
			size_t posBeginUniform = line.find("uniform");
			size_t posBeginComment = line.find("//");
			if (posBeginUniform != std::string::npos && posBeginUniform < posBeginComment) {
				m_uniforms.addUniform(UniformFactory::FromShaderLine(m_shader.getID(), line));
			}
		}
	}
}