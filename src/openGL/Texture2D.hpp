#pragma once

#include <glad/glad.h>

enum PixelFormat {
	RGBA,
	RGB,
	GA,
	A
};

class Texture2D {
public:
	Texture2D();
	void setData(int width, int height, int BPP, unsigned char* pixels = nullptr);
	~Texture2D();

	inline int getWidth() const { return m_width; }
	inline int getHeight() const { return m_height; }
	inline float getAspectRatio() const { return m_aspectRatio; }
	inline int getBPP() const { return m_BPP; }
	inline GLenum getGLpixelFormat() const { return GLpixelFormat(m_pixelFormat); }

	inline unsigned int getID() const { return m_textureID; }

private:
	int m_width;
	int m_height;
	float m_aspectRatio;
	int m_BPP;
	PixelFormat m_pixelFormat;

	unsigned int m_textureID;

private:
	static unsigned int BytesPerPixel(PixelFormat format);
	static GLint GLpixelInternalFormat(PixelFormat format);
	static GLenum GLpixelFormat(PixelFormat format);
};