#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <vector>

enum PixelFormat {
	RGBA,
	RGB,
	GA,
	A
};

class Texture2D {
public:
	Texture2D();
	void Initialize(int width, int height, int BPP, unsigned char* pixels = nullptr);
	~Texture2D();

	void showFullScreen();
	void bind();
	void unbind();

	inline float getAspectRatio() { return m_aspectRatio; }
	inline int getWidth() { return m_width; }
	inline int getHeight() { return m_height; }
	inline int getBPP() { return m_BPP; }
	inline unsigned int getID() { return m_textureID; }
	inline int getSlot() { return m_textureSlot; }

private:
	int m_width;
	int m_height;
	float m_aspectRatio;
	PixelFormat m_pixelFormat;
	int m_BPP;

	unsigned int m_textureID;
	int m_textureSlot;


public:
	static const int MAX_NB_TEXTURES = 8;
	static std::vector<bool> isSlotUsed;
	static void ClassInitialization();

	static unsigned int bytesPerPixel(PixelFormat format);
	static GLint GLpixelInternalFormat(PixelFormat format);
	static GLenum GLpixelFormat(PixelFormat format);
private:
	static size_t showFullScreen_ShaderLID;
};