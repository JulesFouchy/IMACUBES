#include "Texture2D.hpp"

#include "Locator/Locate.hpp"
#include "OpenGL/ShaderLibrary.hpp"
#include "Helper/File.hpp"
#include "Renderer/Renderer.hpp"

#include "Debugging/Log.hpp"
#include "Debugging/gl-exception.h"

size_t Texture2D::showFullScreen_ShaderLID;
std::vector<bool> Texture2D::isSlotUsed;

Texture2D::Texture2D(GLint GLpixelInternalFormat, GLenum GLpixelFormat, GLenum GLpixelType, GLint interpolationMode)
	: m_bytesPerPixel(BytesPerPixel(GLpixelFormat)), m_GLpixelInternalFormat(GLpixelInternalFormat), m_GLpixelFormat(GLpixelFormat), m_GLpixelType(GLpixelType),
	  m_textureSlot(-1)
{
	// Gen texture
	GLCall(glGenTextures(1, &m_textureID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_textureID));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, interpolationMode));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, interpolationMode));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture2D::initialize(int width, int height, unsigned char* pixels) {
	m_width = width;
	m_height = height;
	m_aspectRatio = (float)m_width / m_height;

	GLCall(glBindTexture(GL_TEXTURE_2D, m_textureID));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, m_GLpixelInternalFormat, m_width, m_height, 0, m_GLpixelFormat, m_GLpixelType, pixels));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
void Texture2D::setSize(int width, int height) {
	initialize(width, height, nullptr);
}

void Texture2D::ClassInitialization() {
	for (int i = 0; i < MAX_NB_TEXTURES; ++i)
		isSlotUsed.push_back(false);
	showFullScreen_ShaderLID = Locate::shaderLibrary().LoadShader(MyFile::rootDir+"/res/shaders/_texture.vert", MyFile::rootDir + "/res/shaders/_texture.frag");
}

Texture2D::~Texture2D() {
	GLCall(glDeleteTextures(1, &m_textureID));
}

void Texture2D::showFullScreen() {
	// Bind texture
	attachToSlotAndBind();
	// Shader
	Locate::shaderLibrary()[showFullScreen_ShaderLID].bind();
	Locate::shaderLibrary()[showFullScreen_ShaderLID].setUniform1i("u_TextureSlot", getSlot());
	// Draw call
	Locate::renderer().drawFullScreenQuad();
	// Unbind texture
	detachAndUnbind();
}

void Texture2D::bind() {
	GLCall(glBindTexture(GL_TEXTURE_2D, m_textureID));
}

void Texture2D::unbind() {
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture2D::attachToSlotAndBind() {
	// find slot to bind to
	if (m_textureSlot == -1) {
		auto it = std::find(isSlotUsed.cbegin(), isSlotUsed.cend(), false);
		if (it == isSlotUsed.cend())
			spdlog::error("[Texture2D::attachToSlotAndBind] no empty slot found !");
		else
			m_textureSlot = std::distance(isSlotUsed.cbegin(), it);
	}
	else {
		spdlog::error("[Texture2D::attachToSlotAndBind] not correctly unbound");
	}
	isSlotUsed[m_textureSlot] = true;
	// attach to slot
	GLCall(glActiveTexture(GL_TEXTURE0 + m_textureSlot));
	// bind
	bind();
}

void Texture2D::detachAndUnbind() {
	if (m_textureSlot > -1) {
		isSlotUsed[m_textureSlot] = false;
		m_textureSlot = -1;
		//
		GLCall(glActiveTexture(GL_TEXTURE0));
		unbind();
	}
	else {
		spdlog::warn("[Texture2D::detachAndUnbind] trying to detachAndUnbind a texture that wasn't bound");
	}
}

unsigned int Texture2D::BytesPerPixel(GLenum GLpixelFormat) {
	switch (GLpixelFormat) {
	case GL_RGBA:
		return 4;
	case GL_BGRA:
		return 4;
	case GL_RGB:
		return 3;
	case GL_BGR:
		return 3;
	case GL_RG:
		return 2;
	case GL_RED:
		return 1;
	default:
		spdlog::error("[Texture2D::BytesPerPixel] Unknown pixel format : {}", (int)GLpixelFormat);
	}
}