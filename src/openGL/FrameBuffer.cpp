#include "FrameBuffer.hpp"

#include <glad/glad.h>

#include "Debugging/Log.hpp"
#include "Debugging/gl-exception.h"

FrameBuffer::FrameBuffer()
{
	// Gen FrameBuffer
	GLCall(glGenFramebuffers(1, &m_frameBufferId));
}

FrameBuffer::FrameBuffer(Texture2D& texture)
	: FrameBuffer()
{
	attachTexture(texture);
}

void FrameBuffer::attachTexture(Texture2D& texture) {
	m_texture = &texture;
	// Bind Framebuffer
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferId));
	// Bind and Attach texture
	m_texture->bind();
	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture->getID(), 0));
	// Unbind FrameBuffer
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

FrameBuffer::~FrameBuffer() {
	GLCall(glDeleteFramebuffers(1, &m_frameBufferId));
}

void FrameBuffer::bind() {
	bind_WithoutSettingViewport();
	setViewport();
}

void FrameBuffer::bind_WithoutSettingViewport() {
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferId));
}

void FrameBuffer::setViewport() {
	GLCall(glGetIntegerv(GL_VIEWPORT, m_prevViewportSettings)); // Store viewport settings to restore them when unbinding
	GLCall(glViewport(0, 0, m_texture->getWidth(), m_texture->getHeight()));
}

void FrameBuffer::unbind() {
	unbind_WithoutRestoringViewport();
	restoreViewport();
}


void FrameBuffer::unbind_WithoutRestoringViewport() {
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void FrameBuffer::restoreViewport() {
	GLCall(glViewport(m_prevViewportSettings[0], m_prevViewportSettings[1], m_prevViewportSettings[2], m_prevViewportSettings[3]));
}

void FrameBuffer::clear() {
	// Make sure you have bound the framebuffer beforehand
	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}