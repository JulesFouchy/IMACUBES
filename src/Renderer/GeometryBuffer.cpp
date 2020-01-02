#include "GeometryBuffer.hpp"

#include "Debugging/gl-exception.h"
#include "Debugging/Log.hpp"

#include "Renderer/Renderer.hpp"
#include "Locator/Locate.hpp"

GeometryBuffer::GeometryBuffer()
	: m_positionTexture               (GL_RGB16F,  GL_RGB,  GL_FLOAT,         GL_NEAREST),
	  m_normalShininessTexture        (GL_RGBA16F, GL_RGBA, GL_FLOAT,         GL_NEAREST),
	  m_albedoSpecularintensityTexture(GL_RGBA,    GL_RGBA, GL_UNSIGNED_BYTE, GL_NEAREST)
{
	// Gen and Bind Framebuffer
	GLCall(glGenFramebuffers(1, &m_frameBufferID));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID));
	// Texture attachments
		// Position
	m_positionTexture.bind();
	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_positionTexture.getID(), 0));
		// Normal and Shininess
	m_normalShininessTexture.bind();
	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_normalShininessTexture.getID(), 0));
		// Albedo and Specular intensity
	m_albedoSpecularintensityTexture.bind();
	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, m_albedoSpecularintensityTexture.getID(), 0));
		//
	unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	GLCall(glDrawBuffers(3, attachments));
	// Unbind
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void GeometryBuffer::initialize(int width, int height) {
	// Bind 
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID));
	// Initialize textures
	m_positionTexture.initialize(width, height);
	m_normalShininessTexture.initialize(width, height);
	m_albedoSpecularintensityTexture.initialize(width, height);
	// Depth buffer
	GLCall(glGenRenderbuffers(1, &m_depthRenderBufferID));
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_depthRenderBufferID));
	GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height));
	GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depthRenderBufferID));
	// Check for completeness
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		spdlog::error("[SaveBuffer::SaveBuffer] Framebuffer is not complete!");
	// Unbind
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

GeometryBuffer::~GeometryBuffer() {
	GLCall(glDeleteRenderbuffers(1, &m_depthRenderBufferID));
	GLCall(glDeleteFramebuffers(1, &m_frameBufferID));
}

void GeometryBuffer::bind() {
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID));
}

void GeometryBuffer::unbind() {
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}