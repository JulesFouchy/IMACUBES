#include "ShaderAndItsMaterials.hpp"

ShaderAndItsMaterials::ShaderAndItsMaterials(const std::string& vertexFilepath, const std::string& fragmentFilepath)
	: m_shader(vertexFilepath, fragmentFilepath), m_cubes()
{

}

ShaderAndItsMaterials::~ShaderAndItsMaterials() {

}

void ShaderAndItsMaterials::draw() {
	m_shader.bind();
	m_cubes.draw();
}