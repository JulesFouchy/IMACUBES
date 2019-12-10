#include "MaterialsLocator.hpp"

#include "MaterialsManager.hpp"

Shader& MaterialsLocator::GetShader(int shaderIndex) {
	return MaterialsManager::Shaders()[shaderIndex].m_shader;
}