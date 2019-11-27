#include "ShaderAndItsMaterials.hpp"

#include <fstream>
#include "Helper/String.hpp"

#include "Debugging/Log.hpp"
#include "Types/OpenGLTypes.hpp"
//#include "Types/UniformAbstract.hpp"

ShaderAndItsMaterials::ShaderAndItsMaterials(const std::string& vertexFilepath, const std::string& fragmentFilepath)
	: m_shader(vertexFilepath, fragmentFilepath), m_cubes(0,0,0)
{
	parseShader(fragmentFilepath);
}

ShaderAndItsMaterials::~ShaderAndItsMaterials() {

}

void ShaderAndItsMaterials::draw() {
	m_shader.bind();
	setUniforms();
	m_cubes.draw();
}

void ShaderAndItsMaterials::setUniforms() {
	m_uniforms.set();
}


void ShaderAndItsMaterials::parseShader(const std::string& fragmentFilepath) {
	std::ifstream file(fragmentFilepath);
	if (file.is_open()) {
		//std::vector<Uniform> tmpUniforms;
		//std::string line;
		//while (std::getline(file, line)) {
		//	//spdlog::info("NEW LINE");
		//	// Parse uniform
		//	size_t posBeginUniform = line.find("uniform");
		//	size_t posBeginComment = line.find("//");
		//	if (posBeginUniform != std::string::npos && posBeginUniform < posBeginComment) {
		//		// Get type
		//		size_t posBeginType = MyString::BeginningOfNextWord(line, MyString::EndOfNextWord(line, posBeginUniform) + 1);
		//		size_t posEndType = MyString::EndOfNextWord(line, posBeginType);
		//		OpenGLType type = GLType::FromString(line.substr(posBeginType, posEndType - posBeginType));
		//		//if (thisTypeOfUniformIsAParameter(type)) {
		//			//UniformTypePrecisions uniformTypePrecisions(type);
		//			// Get name
		//			size_t posBeginName = MyString::BeginningOfNextWord(line, posEndType);
		//			size_t posEndName = MyString::EndOfNextWord(line, posBeginName);
		//			std::string s_name = line.substr(posBeginName, posEndName - posBeginName);
		//			spdlog::info("found uniform {}", s_name);
		//			// Get options
		//			/*UniformType initialValue = Uniform::zero(uniformTypePrecisions);
		//			UniformType minValue = Uniform::zero(uniformTypePrecisions);
		//			UniformType maxValue = Uniform::zero(uniformTypePrecisions);
		//			if (posBeginComment != std::string::npos) {
		//				spdlog::info("looking for options");
		//				size_t currentPos = MyString::BeginningOfNextWord(line, MyString::EndOfNextWord(line, posBeginComment) + 1);
		//				while (currentPos < line.size()) {
		//					std::string arg = MyString::GetNextWord(line, &currentPos);
		//					spdlog::info("|" + arg + "|");
		//					if (arg == "NOT_A_COLOR" || arg == "NOT_A_COLOUR") {
		//						uniformTypePrecisions.setShowAsAColorPicker(false);
		//					}
		//					else if (arg == "POINT2D") {
		//						uniformTypePrecisions.setShowAsDraggable2DPoint(true);
		//					}
		//					else if (arg == "default") {
		//						int index = -1;
		//						for (int k = 0; k < m_uniforms.size(); ++k) {
		//							if (m_uniforms[k].getName() == s_name) {
		//								index = k;
		//								break;
		//							}
		//						}
		//						if (index != -1)
		//							initialValue = m_uniforms[index].getValue();
		//						else
		//							initialValue = readValue_s_(uniformTypePrecisions, line, &currentPos);
		//					}
		//					else if (arg == "min") {
		//						minValue = readValue_s_(uniformTypePrecisions, line, &currentPos);
		//					}
		//					else if (arg == "max") {
		//						maxValue = readValue_s_(uniformTypePrecisions, line, &currentPos);
		//					}
		//				}
		//			}*/
		//			// Add uniform
		//			//tmpUniforms.push_back(Uniform(m_shader.getID(), s_name, initialValue, minValue, maxValue, uniformTypePrecisions));
		//			m_uniforms.addUniform(new Uniform<float>(m_shader.getID(), s_name, 0.5f, 0.0f, 1.0f)); // TODO handle all types
		//		//}
		//	}
		//}
		//m_uniforms = tmpUniforms;
	}
}