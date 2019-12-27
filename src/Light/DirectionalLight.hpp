#pragma once

#include "Light.hpp"

class DirectionalLight : public Light {
public:
	DirectionalLight(const glm::vec3& direction, const glm::vec3& color, float intensity, const std::string& name = "DirectionalLight");
	~DirectionalLight() = default;

	void setUniforms(const std::string& uniformName, UniformUpdateList& uniformsList) override;
	void ImGui_Sliders() override;

private:
	glm::vec3 m_direction;
};
