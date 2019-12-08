#include "frameBuffer.hpp"

#include <glad/glad.h>

#include "Debugging/Log.hpp"
#include "Helper/Display.hpp"
#include "Helper/String.hpp"
#include "OpenGL/gl-exception.h"

#include <stb_image/stb_image_write.h>

FrameBuffer::FrameBuffer(int width, int height)
	: m_width(width), m_height(height), m_BPP(4), m_GLpixelFormat(GL_RGBA)
{	
	// Gen and Bind FrameBuffer
	GLCall(glGenFramebuffers(1, &m_frameBufferId));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferId));
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
	// Unbind FrameBuffer
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	// Check for completeness
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		spdlog::error("Framebuffer is not complete!");
}

FrameBuffer::~FrameBuffer() {
	GLCall(glDeleteRenderbuffers(1, &m_colorRenderBufferID));
	GLCall(glDeleteRenderbuffers(1, &m_depthRenderBufferID));
	GLCall(glDeleteFramebuffers(1, &m_frameBufferId));
}

void FrameBuffer::bind() {
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferId));
	GLCall(glGetIntegerv(GL_VIEWPORT, m_prevViewportSettings)); // Store viewport settings to restore them when unbinding
	GLCall(glViewport(0, 0, m_width, m_height));
}

void FrameBuffer::unbind() {
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	GLCall(glViewport(m_prevViewportSettings[0], m_prevViewportSettings[1], m_prevViewportSettings[2], m_prevViewportSettings[3]));
}

void FrameBuffer::clear() {
	// Make sure you have bound the framebuffer beforehand
	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void FrameBuffer::save(const std::string& filePath) {
	// Make sure you have bound the framebuffer beforehand
	if (!filePath.empty()) {
		spdlog::info("[FrameBuffer::save] Saving as " + filePath);
		// Get pixels
		unsigned int width = m_width;
		unsigned int height = m_height;
		unsigned int BPP = m_BPP;
		unsigned char* data = new unsigned char[width * height * BPP];
		GLCall(glReadPixels(0, 0, width, height, m_GLpixelFormat, GL_UNSIGNED_BYTE, data));
		// Save
		stbi_flip_vertically_on_write(1);
		stbi_write_png(filePath.c_str(), width, height, BPP, data, 0);
		// Cleanup
		delete[] data;
		//
		Log::separationLine();
	}
	else {
		spdlog::warn("[FrameBuffer::Save] invalid file path : |{}|", filePath);
	}
}