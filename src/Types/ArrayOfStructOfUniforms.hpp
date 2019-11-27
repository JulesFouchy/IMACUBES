#pragma once

#include "UniformFactory.hpp"

#include <vector>
#include <memory>

class Uniform;

typedef std::vector<Uniform*> StructOfUniforms;

class ArrayOfStructOfUniforms {
public:
	ArrayOfStructOfUniforms();
	~ArrayOfStructOfUniforms() = default;

	void set();

	void addStruct();
	void addUniform(Uniform* uniform);

	void ImGui_Sliders();
private:
	std::vector<StructOfUniforms> m_structOfUniforms;
};