#pragma once
#ifndef __UNIFORM_H
#define __UNIFORM_H

#include "Uniform.hpp"

#include <string>
#include <tuple>

#include "Debugging/Log.hpp"

#include "imgui.h"


template <typename T>
class UniformConcrete : public Uniform {
public:
	UniformConcrete() = default;
	UniformConcrete(GLuint shaderID, const std::string& name, T value, T minValue, T maxValue)
		: Uniform(shaderID, name), m_value(value), m_valueWhenDraggingStarted(value), m_minValue(minValue), m_maxValue(maxValue)
	{}

	void set() override;

	std::tuple<bool, bool, bool> ImGui_Slider() override; // was value modified this frame | did dragging start this frame | did dragging end this frame

	Uniform* createPtrWithSameData() override {
		return new UniformConcrete<T>(m_shaderID, m_name, m_value, m_minValue, m_maxValue);
	}

	Uniform* createFromString(const std::string& line, size_t posEndType) {

	}

	inline T& value() { return m_value; }
	inline const T& getValueWhenDraggingStarted() const { return m_valueWhenDraggingStarted; }
	inline void setValueWhenDraggingStarted(T newValue) { m_valueWhenDraggingStarted = newValue; }
public:
	T m_value;
	T m_valueWhenDraggingStarted;
	T m_minValue;
	T m_maxValue;
};

#endif // !__UNIFORM_H