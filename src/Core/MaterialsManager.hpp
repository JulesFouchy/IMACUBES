#pragma once

#include "ShaderAndItsMaterials.hpp"
#include <vector>

#include "glm/glm.hpp"

struct MaterialLocation {
	int shaderID;
	int MaterialID;
};

class MaterialsManager {
public:
	MaterialsManager() = delete;
	~MaterialsManager() = delete;

	static void draw();
	static void ImGui_Sliders();

	static inline void addShader(const std::string& vertexFilepath, const std::string& fragmentFilepath) { m_shadersList.emplace_back(vertexFilepath, fragmentFilepath, m_shaderCount++); }
	static void updateMatrixUniform(const std::string& name, const glm::mat4& mat);

	static inline std::vector<ShaderAndItsMaterials>& Shaders() { return m_shadersList; }

private:
	static std::vector<ShaderAndItsMaterials> m_shadersList;
	static int m_shaderCount;
};