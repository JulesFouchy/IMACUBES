#pragma once

#include "OpenGL/OpenGLTypes.hpp"
#include "OpenGL/Uniform/UniformConcrete.hpp"
#include <string>

class UniformDescription {
public:
	std::string name;

	UniformDescription(const std::string& name)
		: name(name) {}

	virtual UniformDescription* createPtrWithSameData() = 0;
	virtual Uniform* createUniformPtr(int shaderIndex) = 0;
	virtual void updateThisUniform(Uniform* uniform) = 0;
};