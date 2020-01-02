#include "SaveBuffer.hpp"

#include <glad/glad.h>

#include "Debugging/Log.hpp"
#include "Debugging/gl-exception.h"
#include "Locator/Locate.hpp"
#include "Renderer/Renderer.hpp"
#include "Helper/String.hpp"

#include <stb_image/stb_image_write.h>

SaveBuffer::SaveBuffer(int width, int height, bool bCreateAttachments)
	: m_width(width), m_height(height), m_BPP(4), m_GLpixelFormat(GL_RGBA)
{	
	// Gen and Bind FrameBuffer
	GLCall(glGenFramebuffers(1, &m_frameBufferId));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferId));
	// Create Attachments
	if (bCreateAttachments) {
		createAttachments(width, height);
	// Check for completeness
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			spdlog::error("[SaveBuffer::SaveBuffer] Framebuffer is not complete!");
	}
	// Unbind FrameBuffer
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void SaveBuffer::createAttachments(int width, int height) {
	// Color RenderBuffer
	GLCall(glGenRenderbuffers(1, &m_colorRenderBufferID));
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_colorRenderBufferID));
	GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, width, height));
	GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_colorRenderBufferID));
	// Depth RenderBuffer
	GLCall(glGenRenderbuffers(1, &m_depthRenderBufferID));
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_depthRenderBufferID));
	GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height));
	GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depthRenderBufferID));
}

SaveBuffer::~SaveBuffer() {
	GLCall(glDeleteRenderbuffers(1, &m_colorRenderBufferID));
	GLCall(glDeleteRenderbuffers(1, &m_depthRenderBufferID));
	GLCall(glDeleteFramebuffers(1, &m_frameBufferId));
}

void SaveBuffer::bind() {
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferId));
	GLCall(glGetIntegerv(GL_VIEWPORT, m_prevViewportSettings)); // Store viewport settings to restore them when unbinding
	GLCall(glViewport(0, 0, m_width, m_height));
}

void SaveBuffer::unbind() {
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	GLCall(glViewport(m_prevViewportSettings[0], m_prevViewportSettings[1], m_prevViewportSettings[2], m_prevViewportSettings[3]));
}

void SaveBuffer::clear() {
	// Make sure you have bound the framebuffer beforehand
	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void SaveBuffer::save(const std::string& filePath) {
	// Make sure you have bound the framebuffer beforehand
	if (!filePath.empty()) {
		spdlog::info("[SaveBuffer::save] Saving as " + filePath);
		// Get pixels
		unsigned char* data = getPixelsPtr();
		// Save
		stbi_flip_vertically_on_write(1);
		stbi_write_png(filePath.c_str(), m_width, m_height, m_BPP, data, 0);
		// Cleanup
		delete[] data;
		//
		Log::separationLine();
	}
	else {
		spdlog::warn("[SaveBuffer::Save] invalid file path : |{}|", filePath);
	}
}

unsigned char* SaveBuffer::getPixelsPtr() {
	// Make sure you have bound the framebuffer beforehand
	unsigned char* data = new unsigned char[m_width * m_height * m_BPP];
	GLCall(glReadPixels(0, 0, m_width, m_height, m_GLpixelFormat, GL_UNSIGNED_BYTE, data));
	return data;
}