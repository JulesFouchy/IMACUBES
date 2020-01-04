#pragma once

#include "UniformDescription.hpp"

#include "Uniform.hpp"

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

	UniformAbstract* createUniformPtr() override {
		return new Uniform<T>(name, historyType, defaultValue, minValue, maxValue);
	}

	void updateThisUniform(UniformAbstract* uniform) override {
		((Uniform<T>*) uniform)->m_minValue = minValue;
		((Uniform<T>*) uniform)->m_maxValue = maxValue;
	}
};