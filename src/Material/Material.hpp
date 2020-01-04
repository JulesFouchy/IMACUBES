#pragma once

#include "OpenGL/Uniform/Uniform.hpp"
#include "OpenGL/Uniform/UniformDescription.hpp"

#include <string>

class Material {
public:
	Material(const std::string& name, const std::vector<UniformDescription*>& structLayout, int shaderIndex, int materialIndex);
	Material(const Material& other);
	~Material();

	void updateLayout(const std::vector<UniformDescription*>& structLayout);
	void sendUniforms();

	void ImGui_Sliders();

	inline int getIndex() { return m_materialIndex; }
	inline const std::string& getName() { return m_name; }
	inline std::string* getNamePointer() { return &m_name; }

private:
	int findUniform(const std::string& name);
	void addUniformToStruct(UniformDescription* uniformDescription);
	void updateUniformInsideStruct(int uniformIndex, UniformDescription* uniformDescription);

	inline std::string uniformParamsName(const std::string& uniformName) { return "params[" + std::to_string(m_materialIndex) + "]." + uniformName; }
	inline std::string uniformLightPropName(const std::string& uniformName) { return "lightingProperties[" + std::to_string(m_materialIndex) + "]." + uniformName; }

private:
	std::vector<UniformAbstract*> m_uniformsStruct;
	std::vector<UniformAbstract*> m_lightingProperties;
	int m_shaderIndex;
	int m_materialIndex;
	std::string m_name;
};