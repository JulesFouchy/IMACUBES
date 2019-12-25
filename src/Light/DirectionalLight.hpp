#pragma once

#include "Light.hpp"

class DirectionalLight : public Light {
public:
	DirectionalLight(const glm::vec3& direction, const std::string& name = "DirectionalLight", const glm::vec3& color = glm::vec3(1.0f), float intensity = 1.0f);
	~DirectionalLight() = default;

	void setUniforms(const std::string& uniformName, UniformUpdateList& uniformsList) override;
	void ImGui_Sliders() override;

private:
	glm::vec3 m_direction;
};
