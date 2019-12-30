#pragma once

#include "UniformDescription.hpp"

template <typename T>
class UniformDescriptionConcrete : public UniformDescription {
public:
	T defaultValue;
	T minValue;
	T maxValue;

	UniformDescriptionConcrete(const std::string& name, T defaultValue, T minValue, T maxValue)
		: UniformDescription(name), defaultValue(defaultValue), minValue(minValue), maxValue(maxValue) {}

	UniformDescriptionConcrete* createPtrWithSameData() override {
		return new UniformDescriptionConcrete(name, defaultValue, minValue, maxValue);
	}

	Uniform_ForMaterialSystem* createUniformPtr(int shaderIndex) override {
		return new UniformConcrete<T>(shaderIndex, name, defaultValue, minValue, maxValue);
	}

	void updateThisUniform(Uniform_ForMaterialSystem* uniform) override {
		((UniformConcrete<T>*) uniform)->m_minValue = minValue;
		((UniformConcrete<T>*) uniform)->m_maxValue = maxValue;
	}
};