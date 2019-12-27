#pragma once

#include "Light.hpp"

class PointLight : public Light {
friend class LightsManager;
public:
	PointLight(const glm::vec3& position, const glm::vec3& color, float intensity, const std::string& name = "PointLight");
	~PointLight() = default;

	void setUniforms(const std::string& uniformName, UniformUpdateList& uniformsList) override;
	void ImGui_Sliders() override;

private:
	glm::vec3 m_position;
};