#include "frameBuffer.hpp"

#include <glad/glad.h>

#include "Debugging/Log.hpp"
#include "Helper/Display.hpp"
#include "Helper/String.hpp"
#include "OpenGL/gl-exception.h"

#include <stb_image/stb_image_write.h>

FrameBuffer::FrameBuffer(int width, int height)
	: m_frameBufferId(0), m_texture(), m_prevViewportSettings()
{	
	// Gen Buffer
	GLCall(glGenFramebuffers(1, &m_frameBufferId));
	// Bind
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferId));
	// Attach texture to framebuffer
	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture.getID(), 0));
	// Unbind
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	// Set texture size
	m_texture.setData(width, height, 4);
	// Check for completeness
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		spdlog::error("Framebuffer is not complete!");
}

FrameBuffer::~FrameBuffer() {
	GLCall(glDeleteFramebuffers(1, &m_frameBufferId));
}

void FrameBuffer::bind() {
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferId));
	GLCall(glGetIntegerv(GL_VIEWPORT, m_prevViewportSettings)); // Store viewport settings to restore them when unbinding
	GLCall(glViewport(0, 0, m_texture.getWidth(), m_texture.getHeight()));
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
		unsigned int width = m_texture.getWidth();
		unsigned int height = m_texture.getHeight();
		unsigned int BPP = m_texture.getBPP();
		unsigned char* data = new unsigned char[width * height * BPP];
		GLCall(glReadPixels(0, 0, width, height, m_texture.getGLpixelFormat(), GL_UNSIGNED_BYTE, data));
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