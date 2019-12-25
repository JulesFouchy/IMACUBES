#pragma once

#include <string>
#include <glad/glad.h>

class SaveBuffer {
public:
	SaveBuffer(int width, int height, bool bCreateAttachments = true); // bCreateAttachments = false should only happen during internal calls (used by child classes like SaveBufferMultisampled)
	virtual ~SaveBuffer();

	void bind();
	void unbind();

	void clear(); // Make sure you have bound the framebuffer beforehand
	void save(const std::string& filePath);  // Make sure you have bound the framebuffer beforehand

protected:
	void createAttachments(int width, int height);
	virtual unsigned char* getPixelsPtr();

protected:
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_BPP;
	GLenum m_GLpixelFormat;

	GLuint m_frameBufferId;
	GLuint m_colorRenderBufferID;
	GLuint m_depthRenderBufferID;

	int m_prevViewportSettings[4];
};