#pragma once

#include "OpenGL/Shader.hpp"

class UniformValue {
public:
	UniformValue() = default;
	~UniformValue() = default;

	virtual void set(const std::string& uniforName, Shader& shader) = 0;
};

template <typename T>
class UniformValueConcrete : public UniformValue {
public:
	UniformValueConcrete(const T& value)
		: m_value(value)
	{}

	void set(const std::string& uniformName, Shader& shader) override;
	inline T& get() { return m_value; }

private:
	T m_value;
};