#include "MaterialsLocator.hpp"

#include "Locator/Locate.hpp"

Shader& MaterialsLocator::GetShader(int shaderIndex) {
	return Locate::materialsManager().Shaders()[shaderIndex].shader();
}