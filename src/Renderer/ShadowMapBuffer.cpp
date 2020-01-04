#include "ShadowMapBuffer.hpp"

#include "Debugging/gl-exception.h"

#include "Locator/Locate.hpp"
#include "Renderer.hpp"
#include "Material/MaterialsManager.hpp"
#include "OpenGL/ShaderLibrary.hpp"
#include "Helper/File.hpp"

#include <glm/gtc/matrix_transform.hpp>

size_t ShadowMapBuffer::shadowMapShaderLID;

void ShadowMapBuffer::Initialize() {
	shadowMapShaderLID = Locate::shaderLibrary().LoadShader(MyFile::rootDir+"/res/shaders/_shadowMap.vert", MyFile::rootDir + "/res/shaders/_shadowMap.frag");
}

ShadowMapBuffer::ShadowMapBuffer()
	: m_shadowMap(GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_FLOAT, GL_NEAREST, GL_CLAMP_TO_BORDER),
	  m_width(1024), m_height(1024),
	  m_nearPlane("Near plane", HistoryType::Lights, 0.1f, 0.1f, 2.0f), 
	  m_farPlane("Far plane", HistoryType::Lights, 22.0f, 5.0f, 100.0f),
	  m_bias("Bias", HistoryType::Lights, 0.004f, 0.0f, 0.03f),
	  m_cropFactor("Crop factor", HistoryType::Lights, 11.2f, 1.0f, 100.0f),
	  m_lightDistance("Light distance", HistoryType::Lights, 9.28f, 0.0f, 100.0f)
{
	m_shadowMap.setSize(m_width, m_height);
	m_shadowMap.bind();
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	m_shadowMap.unbind();
	//
	GLCall(glGenFramebuffers(1, &m_frameBufferID));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID)); 
	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_shadowMap.getID(), 0));
	GLCall(glDrawBuffer(GL_NONE));
	GLCall(glReadBuffer(GL_NONE));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

ShadowMapBuffer::ShadowMapBuffer(ShadowMapBuffer&& other) noexcept
	: m_frameBufferID(other.m_frameBufferID), m_shadowMap(std::move(other.m_shadowMap)),
	  m_width(other.m_width), m_height(other.m_height),
	  m_nearPlane(other.m_nearPlane),
	  m_farPlane(other.m_farPlane),
	  m_bias(other.m_bias),
	  m_cropFactor(other.m_cropFactor),
	  m_lightDistance(other.m_lightDistance),
	  m_lightViewMat(other.m_lightViewMat),
	  m_lightProjMat(other.m_lightProjMat),
	  m_lightVPMat(other.m_lightVPMat)

{
	other.m_frameBufferID = -1;
}

void ShadowMapBuffer::initAfterApp(const glm::vec3& lightDir, int dirLightIndex) {
	computeAndSendMatrices(lightDir, dirLightIndex);
}

ShadowMapBuffer::~ShadowMapBuffer() {
	GLCall(glDeleteFramebuffers(1, &m_frameBufferID));
}

void ShadowMapBuffer::compute(const glm::vec3& lightDir, int dirLightIndex) {
	bind();
	//
	computeAndSendMatrices(lightDir, dirLightIndex);
	Locate::shaderLibrary().uniformList(UniformList::Lights).setUniform<float>("u_ShadowBias", m_bias.getValue());
	GLCall(glClear(GL_DEPTH_BUFFER_BIT));
	//GLCall(glCullFace(GL_FRONT));
	Locate::shaderLibrary()[shadowMapShaderLID].bind();
	Locate::materialsManager().draw_WithoutBindingShaders();
	//GLCall(glCullFace(GL_BACK));
	//
	unbind();
}

void ShadowMapBuffer::computeAndSendMatrices(const glm::vec3& lightDir, int dirLightIndex) {
	computeViewMat(lightDir);
	computeProjMat();
	m_lightVPMat = getProjMat() * getViewMat();
	Locate::shaderLibrary().uniformList(UniformList::Lights).setUniform<glm::mat4>("u_LightVPMatrices["+std::to_string(dirLightIndex)+"]", m_lightVPMat);
	Locate::shaderLibrary()[shadowMapShaderLID].bind();
	Locate::shaderLibrary()[shadowMapShaderLID].setUniformMat4f("u_LightVPMatrix", m_lightVPMat);
}

void ShadowMapBuffer::computeViewMat(const glm::vec3& lightDir) {
	m_lightViewMat = glm::lookAt(-lightDir*m_lightDistance.getValue(),
								 glm::vec3(0.0f, 0.0f, 0.0f),
								 glm::vec3(0.0f, 1.0f, 0.0f));
}

void ShadowMapBuffer::computeProjMat() {
	float c = m_cropFactor.getValue();
	m_lightProjMat = glm::ortho(-c, c, -c, c, m_nearPlane.getValue(), m_farPlane.getValue());
}


void ShadowMapBuffer::bind() {
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID));
	GLCall(glGetIntegerv(GL_VIEWPORT, m_prevViewportSettings)); // Store viewport settings to restore them when unbinding
	GLCall(glViewport(0, 0, m_width, m_height));
}

void ShadowMapBuffer::unbind() {
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	GLCall(glViewport(m_prevViewportSettings[0], m_prevViewportSettings[1], m_prevViewportSettings[2], m_prevViewportSettings[3]));
}

void ShadowMapBuffer::ImGui_Parameters() {
	m_bias.ImGui_Slider();
	m_nearPlane.ImGui_Slider();
	m_farPlane.ImGui_Slider();
	m_lightDistance.ImGui_Slider();
	m_cropFactor.ImGui_Slider();
}