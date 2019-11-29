#pragma once

#include "OpenGL/Uniform/UniformFactory.hpp"

#include <vector>
#include <memory>

class Uniform;

typedef std::vector<Uniform*> StructOfUniforms;

class ArrayOfStructOfUniforms {
public:
	ArrayOfStructOfUniforms();
	~ArrayOfStructOfUniforms();

	void setUniforms();

	void addStruct();
	void addUniform(Uniform* uniform);

	void ImGui_Sliders(const std::string& windowName);

	int find(const std::string& uniformName);

	inline std::vector<StructOfUniforms>& structsOfUniforms() { return m_structsOfUniforms; };
	inline int nbOfStructs() { return m_structsOfUniforms.size();  }

private:
	std::vector<StructOfUniforms> m_structsOfUniforms;
};