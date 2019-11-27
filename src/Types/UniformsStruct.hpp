#pragma once

#include "OpenGLTypes.hpp"

#include <vector>

class UniformStruct {
public:
	UniformStruct();
	~UniformStruct();

	void* operator[] (unsigned int index) const;

	void showGUI();

	void addUniform(OpenGLType type, const std::string& name);

private:
	static unsigned int SizeOf(OpenGLType type);

public:
	std::vector<OpenGLType> m_TypesList;
	std::vector<std::string> m_UniformNamesList;
	std::vector<unsigned int> m_offsetToDataInBytes;
	void* m_dataPtr;
};