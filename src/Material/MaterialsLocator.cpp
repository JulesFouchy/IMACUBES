#include "MaterialsLocator.hpp"

#include "Locator/MaterialManagerLocator.hpp"

Shader& MaterialsLocator::GetShader(int shaderIndex) {
	return Locate::materialsManager().Shaders()[shaderIndex].m_shader;
}