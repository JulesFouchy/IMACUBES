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

	void setUniforms();

	void addStruct();
	void addUniform(Uniform* uniform);

	void ImGui_Sliders(const std::string& windowName);
private:
	std::vector<StructOfUniforms> m_structsOfUniforms;
};