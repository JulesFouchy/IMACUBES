#include "MaterialsLocator.hpp"

#include "MaterialsManager.hpp"

Shader& MaterialsLocator::GetShader(int shaderIndex) {
	return MaterialsManager::m_shadersList[shaderIndex].m_shader;
}