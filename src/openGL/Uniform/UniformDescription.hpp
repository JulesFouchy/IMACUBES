#pragma once

#include "OpenGL/OpenGLTypes.hpp"
#include "OpenGL/Uniform/Uniform.hpp"
#include "History/HistoryTypes.hpp"

#include <string>

class UniformDescription {
public:
	std::string name;
	HistoryType historyType;

	UniformDescription(const std::string& name, HistoryType historyType)
		: name(name), historyType(historyType) {}

	virtual UniformDescription* createPtrWithSameData() = 0;
	virtual UniformAbstract* createUniformPtr() = 0;
	virtual void updateThisUniform(UniformAbstract* uniform) = 0;
};