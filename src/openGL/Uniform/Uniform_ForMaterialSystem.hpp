#pragma once

#include <glad/glad.h>
#include <string>

#include "OpenGL/Shader.hpp"

#include "Debugging/Log.hpp"

#include "Material/MaterialsLocator.hpp"

class Uniform_ForMaterialSystem {
friend class UniformDescription;
public:
	Uniform_ForMaterialSystem(int shaderIndex, const std::string& nameInsideStruct)
		: m_shaderIndex(shaderIndex), m_nameInsideStruct(nameInsideStruct)
	{}
	~Uniform_ForMaterialSystem() = default;

	virtual void set(int structIndex) = 0;
	
	virtual void ImGui_Slider() = 0;

	virtual Uniform_ForMaterialSystem* createPtrWithSameData() = 0;

	inline Shader& getShader() { return MaterialsLocator::GetShader(m_shaderIndex); }
	inline const std::string getNameFull(int structIndex) const { return std::string("params[") + std::to_string(structIndex) + std::string("].") + m_nameInsideStruct; }
	inline const std::string& getNameInsideStruct() const { return m_nameInsideStruct; }
protected:
	int m_shaderIndex;
	std::string m_nameInsideStruct;
};