#include "MaterialsForAGivenShader.hpp"

#include <fstream>
#include "Helper/String.hpp"

#include "Debugging/Log.hpp"
#include "OpenGL/OpenGLTypes.hpp"
#include "OpenGL/Uniform/UniformFactory.hpp"

MaterialsForAGivenShader::MaterialsForAGivenShader(const std::string& vertexFilepath, const std::string& fragmentFilepath, int shaderIndex)
	: m_shader(vertexFilepath, fragmentFilepath), m_cubes(0,0,0), m_name(MyString::RemoveFileExtension(MyString::RemoveFolderHierarchy(fragmentFilepath))), m_shaderIndex(shaderIndex), m_uniforms(shaderIndex)
{
	m_uniforms.addStruct(m_name);
	parseShader(fragmentFilepath);
}

MaterialsForAGivenShader::~MaterialsForAGivenShader() {
	m_uniforms.deleteAllPointers();
}

void MaterialsForAGivenShader::draw() {
	m_shader.bind();
	setUniforms();
	m_cubes.draw();
}

void MaterialsForAGivenShader::reloadShader() {
	m_shader.compile();
	parseShader(m_shader.getFragmentFilepath());
}

void MaterialsForAGivenShader::ImGui_Menu(){
	ImGui::PushID((int)this);
		ImGui::Text(m_name.c_str());
		if (ImGui::Button("Add Material")) {
			m_uniforms.addStruct(m_name);
		}
		m_uniforms.ImGui_Sliders(); 
	ImGui::Separator();
	ImGui::PopID();
}

void MaterialsForAGivenShader::setUniforms() {
	m_uniforms.setUniforms();
	//for (int k = 0; k < m_uniforms.nbOfStructs(); ++k) {
	//	m_shader.setUniform1i("materialIndices["+std::to_string(k)+"]", 1);
	//}
}


void MaterialsForAGivenShader::parseShader(const std::string& fragmentFilepath) {
	/*ArrayOfStructOfUniforms newUniforms(m_shaderIndex);
	for (int k = 0; k < m_uniforms.nbOfStructs(); ++k) {
		newUniforms.addStruct(m_name);
	}*/
	std::ifstream file(fragmentFilepath);
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			// Look for 'struct MaterialParameters'
			if (line.find("struct MaterialParameters") != std::string::npos) { // TODO check that the line isn't commented out
				std::getline(file, line);
				while (line.find("}") == std::string::npos) {
					// Check if the uniform already existed
					size_t currentPos = 0;
					MyString::GetNextWord(line, &currentPos); // skip type
					std::string name = MyString::GetNextWord(line, &currentPos);
					//spdlog::info("found uni |{}|", name);
					int uniformIndex = m_uniforms.find(name);
					if (uniformIndex == -1) {
						m_uniforms.addUniform(UniformFactory::FromShaderLine(m_shaderIndex, line));
					}
					/*else {
						newUniforms.addUniform(m_uniforms.structsOfUniforms()[0][uniformIndex]);
						for (int k = 0; k < m_uniforms.nbOfStructs(); ++k) {
							newUniforms.structsOfUniforms()[k].back() = m_uniforms.structsOfUniforms()[k][uniformIndex];
						}
					}*/
					// Go to next line
					std::getline(file, line);
				}
			}
		}
	}
	//m_uniforms = newUniforms;
}