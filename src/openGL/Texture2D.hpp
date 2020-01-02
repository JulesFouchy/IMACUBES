#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <vector>

class Texture2D {
public:
	Texture2D(GLint GLpixelInternalFormat = GL_RGBA8, GLenum GLpixelFormat = GL_RGBA, GLenum GLpixelType = GL_UNSIGNED_BYTE, GLint interpolationMode = GL_LINEAR);
	void initialize(int width, int height, unsigned char* pixels = nullptr);
	~Texture2D();

	void showFullScreen();
	void bind();
	void unbind();
	void attachToSlotAndBind();
	void detachAndUnbind();

	inline float getAspectRatio() { return m_aspectRatio; }
	inline int getWidth() { return m_width; }
	inline int getHeight() { return m_height; }
	inline int getBPP() { return m_bytesPerPixel; }
	inline unsigned int getID() { return m_textureID; }
	inline int getSlot() { return m_textureSlot; }

private:
	int m_width;
	int m_height;
	float m_aspectRatio;

	unsigned int m_bytesPerPixel;
	GLint m_GLpixelInternalFormat;
	GLenum m_GLpixelFormat;
	GLenum m_GLpixelType;

	unsigned int m_textureID;
	int m_textureSlot;

public:
	static const int MAX_NB_TEXTURES = 8;
	static std::vector<bool> isSlotUsed;
	static void ClassInitialization();

	static unsigned int BytesPerPixel(GLenum GLpixelFormat);

private:
	static size_t showFullScreen_ShaderLID;
};