#pragma once

#include "UniformDescription.hpp"

#include "UniformConcrete.hpp"

template <typename T>
class UniformDescriptionConcrete : public UniformDescription {
public:
	T defaultValue;
	T minValue;
	T maxValue;

	UniformDescriptionConcrete(const std::string& name, HistoryType historyType, T defaultValue, T minValue, T maxValue)
		: UniformDescription(name, historyType), defaultValue(defaultValue), minValue(minValue), maxValue(maxValue) {}

	UniformDescription* createPtrWithSameData() override {
		return new UniformDescriptionConcrete(name, historyType, defaultValue, minValue, maxValue);
	}

	Uniform* createUniformPtr() override {
		return new UniformConcrete<T>(historyType, defaultValue, minValue, maxValue, name);
	}

	void updateThisUniform(Uniform* uniform) override {
		((UniformConcrete<T>*) uniform)->m_minValue = minValue;
		((UniformConcrete<T>*) uniform)->m_maxValue = maxValue;
	}
};