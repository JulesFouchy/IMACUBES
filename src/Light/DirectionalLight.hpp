#pragma once

#include "Light.hpp"

#include "Helper/SphericalCoordinates_AngularPart.hpp"

#include "Renderer/ShadowMapBuffer.hpp"

class DirectionalLight : public Light {
friend class LightsManager;
public:
	DirectionalLight(int dirLightIndex, float angleUp, float angleGround, const glm::vec3& color, float intensity, const std::string& name = "DirectionalLight");
	DirectionalLight(const DirectionalLight& other) = delete;
	DirectionalLight(DirectionalLight&& other) noexcept;
	~DirectionalLight() = default;

	void setUniforms(const std::string& uniformName, UniformUpdateList& uniformsList) override;
	void computeShadowMap();
	Texture2D& shadowMap();
	void ImGui_ShadowParameters();

	void ImGui_Sliders() override;

private:
	int m_dirLightIndex;
	Uniform<SphericalCoordinates_AngularPart> m_direction;

	ShadowMapBuffer m_shadowMapBuffer;
};
