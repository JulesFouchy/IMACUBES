#include "UniformsStruct.hpp"
#include "Debugging/Log.hpp"

UniformStruct::UniformStruct() {
	m_dataPtr = malloc(20 * sizeof(float));
	m_offsetToDataInBytes.push_back(0);
}

UniformStruct::~UniformStruct() {
	free(m_dataPtr);
}

void* UniformStruct::operator[](unsigned int index) const {
	return (char*)m_dataPtr + m_offsetToDataInBytes[index];
}

void UniformStruct::addType(OpenGLType type) {
	m_TypesList.push_back(type);
	m_offsetToDataInBytes.push_back(m_offsetToDataInBytes.back() + SizeOf(type));
}

unsigned int UniformStruct::SizeOf(OpenGLType type) {
	switch (type)
	{
	case Int:
		return sizeof(int);
		break;
	case Float:
		return sizeof(float);
		break;
	case Vec2:
		return 2*sizeof(float);
		break;
	case Vec3:
		return 3*sizeof(float);
		break;
	case Vec4:
		break;
		return 4*sizeof(float);
	default:
		spdlog::error("[UniformStruct::SizeOf] Unknown type : {}", type);
		break;
	}
}