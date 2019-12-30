#pragma once

#include "Light.hpp"

#include "Helper/SphericalCoordinates_AngularPart.hpp"

class DirectionalLight : public Light {
friend class LightsManager;
public:
	DirectionalLight(float angleUp, float angleGround, const glm::vec3& color, float intensity, const std::string& name = "DirectionalLight");
	~DirectionalLight() = default;

	void setUniforms(const std::string& uniformName, UniformUpdateList& uniformsList) override;
	void ImGui_Sliders() override;

private:
	SphericalCoordinates_AngularPart m_direction;
};
