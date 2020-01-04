#include "DirectionalLight.hpp"

#include <imgui/imgui.h>

DirectionalLight::DirectionalLight(int dirLightIndex, float angleUp, float angleGround, const glm::vec3& color, float intensity, const std::string& name)
	: Light(name, color, intensity), m_dirLightIndex(dirLightIndex), m_direction("", HistoryType::Lights, SphericalCoordinates_AngularPart(angleUp, angleGround)),
	  m_bCastShadows(true)
{
	m_shadowMapBuffer.initAfterApp(((SphericalCoordinates_AngularPart*)&m_direction.getValue())->getXYZ(), dirLightIndex);
}

DirectionalLight::DirectionalLight(DirectionalLight&& other) noexcept
	: Light(other), m_dirLightIndex(other.m_dirLightIndex), m_direction(other.m_direction), m_bCastShadows(other.m_bCastShadows), m_shadowMapBuffer(std::move(other.m_shadowMapBuffer))
{

}

void DirectionalLight::setUniforms(const std::string& uniformName, UniformUpdateList& uniformsList) {
	Light::setUniforms(uniformName, uniformsList);
	glm::vec3 dir = ((SphericalCoordinates_AngularPart*) &m_direction.getValue())->getXYZ(); // Type pun to remove const (getXYZ is quasi const so it's OK)
	uniformsList.setUniform(uniformName + ".direction", dir);
	//
	uniformsList.setUniform("u_bCastShadows[" + std::to_string(m_dirLightIndex) + "]", (int)m_bCastShadows);
}

void DirectionalLight::computeShadowMap(){
	m_shadowMapBuffer.compute(((SphericalCoordinates_AngularPart*)&m_direction.getValue())->getXYZ(), m_dirLightIndex); // Type pun to remove const (getXYZ is quasi const so it's OK)
}

Texture2D& DirectionalLight::shadowMap() {
	return m_shadowMapBuffer.texture();
}

void DirectionalLight::ImGui_ShadowParameters() {
	if (ImGui::BeginMenu(("Dir Light " + std::to_string(m_dirLightIndex)).c_str())) {
		ImGui::Checkbox("Active", &m_bCastShadows);
		m_shadowMapBuffer.ImGui_Parameters();
		ImGui::EndMenu();
	}
}

void DirectionalLight::ImGui_Sliders() {
	Light::ImGui_Sliders();
	ImGui::Separator();
	m_direction.ImGui_Slider();
}