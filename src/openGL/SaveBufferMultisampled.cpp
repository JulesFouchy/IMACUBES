#include "SaveBufferMultisampled.hpp"

#include "Debugging/gl-exception.h"
#include "Debugging/Log.hpp"

SaveBufferMultisampled::SaveBufferMultisampled(int width, int height, int nbSamples)
	: SaveBuffer(width, height, false)
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferId));
	// Create attachments
	createAttachments(width, height, nbSamples);
	// Create buffer used during blit (taking a multisampled buffer and converting it into a usual buffer)
	GLCall(glGenFramebuffers(1, &m_BLITframeBufferId));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_BLITframeBufferId));
		// Color RenderBuffer
	GLCall(glGenRenderbuffers(1, &m_BLITcolorRenderBufferID));
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_BLITcolorRenderBufferID));
	GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, width, height));
	GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_BLITcolorRenderBufferID));
	// Check for completeness
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		spdlog::error("[SaveBufferMultisampled::SaveBufferMultisampled] Framebuffer is not complete!");
	// Unbind FrameBuffer
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void SaveBufferMultisampled::createAttachments(int width, int height, int nbSamples) {
	assert(nbSamples > 0);  // 0 samples would be weird
	// Color RenderBuffer
	GLCall(glGenRenderbuffers(1, &m_colorRenderBufferID));
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_colorRenderBufferID));
	GLCall(glRenderbufferStorageMultisample(GL_RENDERBUFFER, nbSamples, GL_RGBA8, width, height));
	GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_colorRenderBufferID));
	// Depth RenderBuffer
	GLCall(glGenRenderbuffers(1, &m_depthRenderBufferID));
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_depthRenderBufferID));
	GLCall(glRenderbufferStorageMultisample(GL_RENDERBUFFER, nbSamples, GL_DEPTH24_STENCIL8, width, height));
	GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depthRenderBufferID));
}

SaveBufferMultisampled::~SaveBufferMultisampled() {
	GLCall(glDeleteRenderbuffers(1, &m_BLITcolorRenderBufferID));
	GLCall(glDeleteFramebuffers(1, &m_BLITframeBufferId));
}

unsigned char* SaveBufferMultisampled::getPixelsPtr() {
	// Make sure you have bound the framebuffer beforehand
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_BLITframeBufferId);
	glBlitFramebuffer(0, 0, m_width, m_height, 0, 0, m_width, m_height, GL_COLOR_BUFFER_BIT, GL_NEAREST);

	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_BLITframeBufferId);
	unsigned char* data = new unsigned char[m_width * m_height * m_BPP];
	GLCall(glReadPixels(0, 0, m_width, m_height, m_GLpixelFormat, GL_UNSIGNED_BYTE, data));

	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferId);

	return data;
}