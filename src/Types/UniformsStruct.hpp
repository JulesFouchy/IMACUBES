#pragma once

#include "OpenGLTypes.hpp"

#include <vector>

class UniformStruct {
public:
	UniformStruct();
	~UniformStruct();

	void* operator[] (unsigned int index) const;

	void addType(OpenGLType type);

private:
	static unsigned int SizeOf(OpenGLType type);

private:
	std::vector<OpenGLType> m_TypesList;
	std::vector<unsigned int> m_offsetToDataInBytes;
	void* m_dataPtr;
};