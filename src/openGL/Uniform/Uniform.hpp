#pragma once

#include <glad/glad.h>
#include <string>

#include "OpenGL/Shader.hpp"

#include "Core/MaterialsLocator.hpp"

class Uniform {
public:
	Uniform(int shaderIndex, const std::string& nameInsideStruct)
		: m_shaderIndex(shaderIndex), m_nameInsideStruct(nameInsideStruct)
	{}
	~Uniform() = default;

	virtual void set(int structIndex) = 0;
	
	virtual std::tuple<bool, bool, bool> ImGui_Slider() = 0; // RETURNS : was value modified this frame / did dragging start this frame / did dragging end this frame

	virtual Uniform* createPtrWithSameData() = 0;

	inline Shader& getShader() { return MaterialsLocator::GetShader(m_shaderIndex); }
	inline const std::string getNameFull(int structIndex) const { return std::string("params[") + std::to_string(structIndex) + std::string("].") + m_nameInsideStruct; }
	inline const std::string& getNameInsideStruct() const { return m_nameInsideStruct; }
protected:
	int m_shaderIndex;
	std::string m_nameInsideStruct;
};