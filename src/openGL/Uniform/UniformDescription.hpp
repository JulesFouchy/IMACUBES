#pragma once

#include "OpenGL/OpenGLTypes.hpp"
#include "OpenGL/Uniform/Uniform_ForMaterialSystemConcrete.hpp"
#include <string>

class UniformDescription {
public:
	std::string name;

	UniformDescription(const std::string& name)
		: name(name) {}

	virtual UniformDescription* createPtrWithSameData() = 0;
	virtual Uniform_ForMaterialSystem* createUniformPtr(int shaderIndex) = 0;
	virtual void updateThisUniform(Uniform_ForMaterialSystem* uniform) = 0;
};