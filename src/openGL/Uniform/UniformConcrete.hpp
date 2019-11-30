#pragma once

#include "Uniform.hpp"

#include <string>
#include <tuple>
#include "Debugging/Log.hpp"
#include "imgui.h"

template <typename T>
class UniformConcrete : public Uniform {
public:
	UniformConcrete() = default;
	UniformConcrete(Shader* shader, const std::string& nameInsideStruct, T value, T minValue, T maxValue)
		: Uniform(shader, nameInsideStruct), m_value(value), m_valueWhenDraggingStarted(value), m_minValue(minValue), m_maxValue(maxValue)
	{}

	void set(int structIndex) override;

	std::tuple<bool, bool, bool> ImGui_Slider() override; // RETURNS : was value modified this frame / did dragging start this frame / did dragging end this frame

	Uniform* createPtrWithSameData() override {
		return new UniformConcrete<T>(m_shader, getNameInsideStruct(), m_value, m_minValue, m_maxValue);
	}

	inline T& value() { return m_value; }
	//inline const T& getValueWhenDraggingStarted() const { return m_valueWhenDraggingStarted; }
	//inline void setValueWhenDraggingStarted(T newValue) { m_valueWhenDraggingStarted = newValue; }
public:
	T m_value;
	T m_valueWhenDraggingStarted;
	T m_minValue;
	T m_maxValue;
};