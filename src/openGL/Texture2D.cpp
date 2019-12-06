#include "Texture2D.hpp"

#include "Debugging/Log.hpp"
#include "OpenGL/gl-exception.h"

Texture2D::Texture2D()
	  // Dummy initialization
	: m_width(0), m_height(0), m_aspectRatio(1.0f), m_BPP(0), m_pixelFormat(RGBA), m_textureID(0)
{
	// Gen texture
	GLCall(glGenTextures(1, &m_textureID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_textureID));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture2D::setData(int width, int height, int BPP, unsigned char* pixels){
	m_BPP = BPP;
	m_width = width;
	m_height = height;
	m_aspectRatio = (float)m_width / m_height;

	GLCall(glBindTexture(GL_TEXTURE_2D, m_textureID));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GLpixelInternalFormat(m_pixelFormat), m_width, m_height, 0, GLpixelFormat(m_pixelFormat), GL_UNSIGNED_BYTE, pixels));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

Texture2D::~Texture2D() {
	GLCall(glDeleteTextures(1, &m_textureID));
}

unsigned int Texture2D::BytesPerPixel(PixelFormat format) {
	switch (format) {
	case RGBA:
		return 4;
		break;
	case RGB:
		return 3;
		break;
	case GA:
		return 2;
		break;
	case A:
		return 1;
		break;
	default:
		spdlog::error("[Texture2D::bytesPerPixel] Unknown pixel format : {}", format);
		break;
	}
}

GLint Texture2D::GLpixelInternalFormat(PixelFormat format) {
	switch (format) {
	case RGBA:
		return GL_RGBA8;
		break;
	case RGB:
		return GL_RGB8;
		break;
	case GA:
		return GL_RG8;
		break;
	case A:
		return GL_R8;
		break;
	default:
		spdlog::error("[Texture2D::GLpixelInternalFormat] Unknown pixel format {}", format);
		break;
	}
}

GLenum Texture2D::GLpixelFormat(PixelFormat format) {
	switch (format) {
	case RGBA:
		return GL_RGBA;
		break;
	case RGB:
		return GL_RGB;
		break;
	case GA:
		return GL_RG;
		break;
	case A:
		return GL_R;
		break;
	default:
		spdlog::error("[Texture2D::GLpixelFormat] Unknown pixel format {}", format);
		break;
	}
}