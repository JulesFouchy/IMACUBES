#pragma once

#include "OpenGL/Uniform/UniformFactory.hpp"

#include <vector>
#include <memory>

class Uniform;

typedef std::vector<Uniform*> StructOfUniforms;

class ArrayOfStructOfUniforms {
public:
	ArrayOfStructOfUniforms(int shaderIndex);
	ArrayOfStructOfUniforms(const ArrayOfStructOfUniforms& other);
	~ArrayOfStructOfUniforms() = default;
	void deleteAllPointers();

	void setUniforms();

	void addStruct(const std::string& shaderName);
	void addUniform(Uniform* uniform);

	void ImGui_Sliders();

	int find(const std::string& uniformName);

	inline std::vector<StructOfUniforms>& structsOfUniforms() { return m_structsOfUniforms; };
	inline int nbOfStructs() { return m_structsOfUniforms.size();  }

private:
	std::vector<StructOfUniforms> m_structsOfUniforms;
	std::vector<std::string> m_structNames;
	int m_shaderIndex;
};