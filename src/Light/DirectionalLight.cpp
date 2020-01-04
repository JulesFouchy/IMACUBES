#include "DirectionalLight.hpp"

#include <imgui/imgui.h>

DirectionalLight::DirectionalLight(float angleUp, float angleGround, const glm::vec3& color, float intensity, const std::string& name)
	: Light(name, color, intensity), m_direction("", HistoryType::Lights, SphericalCoordinates_AngularPart(angleUp, angleGround))
{
	m_shadowMapBuffer.initAfterApp(((SphericalCoordinates_AngularPart*)&m_direction.getValue())->getXYZ());
}

void DirectionalLight::setUniforms(const std::string& uniformName, UniformUpdateList& uniformsList) {
	Light::setUniforms(uniformName, uniformsList);
	glm::vec3 dir = ((SphericalCoordinates_AngularPart*) &m_direction.getValue())->getXYZ(); // Type pun to remove const (getXYZ is quasi const so it's OK)
	uniformsList.setUniform(uniformName + ".direction", dir);
}

void DirectionalLight::computeShadowMap(){
	m_shadowMapBuffer.compute(((SphericalCoordinates_AngularPart*)&m_direction.getValue())->getXYZ()); // Type pun to remove const (getXYZ is quasi const so it's OK)
}

Texture2D& DirectionalLight::getShadowMap() {
	return m_shadowMapBuffer.texture();
}

void DirectionalLight::ImGui_Sliders() {
	Light::ImGui_Sliders();
	ImGui::Separator();
	m_direction.ImGui_Slider();
}