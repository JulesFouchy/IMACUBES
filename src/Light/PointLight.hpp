#pragma once

#include "Light.hpp"

class PointLight : public Light {
public:
	PointLight(const glm::vec3& position, const std::string& name = "PointLight", const glm::vec3& color = glm::vec3(1.0f), float intensity = 5.0f);
	~PointLight() = default;

	void setUniforms(const std::string& uniformName, UniformUpdateList& uniformsList) override;
	void ImGui_Sliders() override;

private:
	glm::vec3 m_position;
};