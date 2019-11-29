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
	m_uniforms.deleteAllPointers();
}

void ShaderAndItsMaterials::draw() {
	m_shader.bind();
	setUniforms();
	m_cubes.draw();
}

void ShaderAndItsMaterials::reloadShader() {
	m_shader.compile();
	parseShader(m_shader.getFragmentFilepath());
}

void ShaderAndItsMaterials::setUniforms() {
	m_uniforms.setUniforms();
}


void ShaderAndItsMaterials::parseShader(const std::string& fragmentFilepath) {
	ArrayOfStructOfUniforms newUniforms;
	for (int k = 0; k < m_uniforms.nbOfStructs(); ++k) {
		newUniforms.addStruct();
	}
	std::ifstream file(fragmentFilepath);
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			// Look for 'uniform'
			size_t posBeginUniform = line.find("uniform");
			size_t posBeginComment = line.find("//");
			if (posBeginUniform != std::string::npos && posBeginUniform < posBeginComment) {
				// Check if the uniform already existed
				MyString::GetNextWord(line, &posBeginUniform); // skip type
				std::string name = MyString::GetNextWord(line, &posBeginUniform);
				int uniformIndex = m_uniforms.find(name);
				if (uniformIndex == -1) {
					newUniforms.addUniform(UniformFactory::FromShaderLine(&m_shader, line));
				}
				else {
					spdlog::info("uni {} alrezady exists", name);
					for (int k = 0; k < m_uniforms.nbOfStructs(); ++k) {
						newUniforms.structsOfUniforms()[k][uniformIndex] = m_uniforms.structsOfUniforms()[k][uniformIndex];
					}
				}
			}
		}
	}
	m_uniforms = newUniforms;
}