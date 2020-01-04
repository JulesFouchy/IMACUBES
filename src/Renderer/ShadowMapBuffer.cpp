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
	: m_shadowMap(GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_FLOAT, GL_NEAREST, GL_REPEAT),
	  m_width(1024), m_height(1024),
	  m_nearPlane(1.0f), m_farPlane(7.5f)
{
	computeMatrices();
	//
	m_shadowMap.setSize(m_width, m_height);
	GLCall(glGenFramebuffers(1, &m_frameBufferID));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID)); 
	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_shadowMap.getID(), 0));
	GLCall(glDrawBuffer(GL_NONE));
	GLCall(glReadBuffer(GL_NONE));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

ShadowMapBuffer::~ShadowMapBuffer() {
	GLCall(glDeleteFramebuffers(1, &m_frameBufferID));
}

void ShadowMapBuffer::compute() {
	GLCall(glViewport(0, 0, m_width, m_height));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID));
	//
	GLCall(glClear(GL_DEPTH_BUFFER_BIT));
	Locate::shaderLibrary()[shadowMapShaderLID].bind();
	Locate::shaderLibrary()[shadowMapShaderLID].setUniformMat4f("u_LightVPMatrix", getViewProjMat());
	Locate::materialsManager().draw_WithoutBindingShaders();
	//
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	GLCall(glViewport(0, 0, Locate::renderer().getWidth(), Locate::renderer().getHeight()));
}

void ShadowMapBuffer::computeMatrices() {
	computeViewMat();
	computeProjMat();
	m_lightVPMat = getProjMat() * getViewMat();
}

void ShadowMapBuffer::computeViewMat() {
	m_lightViewMat = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f),
								 glm::vec3(0.0f, 0.0f, 0.0f),
								 glm::vec3(0.0f, 1.0f, 0.0f));
}

void ShadowMapBuffer::computeProjMat() {
	m_lightProjMat = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, m_nearPlane, m_farPlane);
}