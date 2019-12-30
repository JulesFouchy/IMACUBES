#include "MaterialsLocator.hpp"

#include "Locator/Locate.hpp"
#include "MaterialsManager.hpp"

Shader& MaterialsLocator::GetShader(int shaderIndex) {
	return Locate::materialsManager().Shaders()[shaderIndex].shader();
}