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
	  m_nearPlane(1.0f), m_farPlane(7.5f)
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

void ShadowMapBuffer::initAfterApp() {
	computeAndSendMatrices();
}

ShadowMapBuffer::~ShadowMapBuffer() {
	GLCall(glDeleteFramebuffers(1, &m_frameBufferID));
}

void ShadowMapBuffer::compute() {
	GLCall(glViewport(0, 0, m_width, m_height));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID));
	//
	computeAndSendMatrices();
	GLCall(glClear(GL_DEPTH_BUFFER_BIT));
	//GLCall(glCullFace(GL_FRONT));
	Locate::materialsManager().draw_WithoutBindingShaders();
	//GLCall(glCullFace(GL_BACK));
	//
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	GLCall(glViewport(0, 0, Locate::renderer().getWidth(), Locate::renderer().getHeight()));
}

void ShadowMapBuffer::computeAndSendMatrices() {
	computeViewMat();
	computeProjMat();
	m_lightVPMat = getProjMat() * getViewMat();
	Locate::shaderLibrary().uniformList(UniformList::Lights).setUniform<glm::mat4>("u_LightVPMatrix", m_lightVPMat);
	Locate::shaderLibrary()[shadowMapShaderLID].bind();
	Locate::shaderLibrary()[shadowMapShaderLID].setUniformMat4f("u_LightVPMatrix", m_lightVPMat);
}

void ShadowMapBuffer::computeViewMat() {
	m_lightViewMat = glm::lookAt(glm::vec3(20.0f, 8.0f, -1.0f)*0.1f,
								 glm::vec3(0.0f, 0.0f, 0.0f),
								 glm::vec3(0.0f, 1.0f, 0.0f));
}

void ShadowMapBuffer::computeProjMat() {
	m_lightProjMat = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, m_nearPlane, m_farPlane);
}