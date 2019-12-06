#pragma once

#include "Texture2D.hpp"

#include <string>

class FrameBuffer {
public: 
	FrameBuffer(int width, int height);
	~FrameBuffer();

	void bind();
	void unbind();

	void clear(); // Make sure you have bound the framebuffer beforehand
	void save(const std::string& filePath);  // Make sure you have bound the framebuffer beforehand

	inline Texture2D& getColorTexture() { return m_colorTexture; }

private:
	unsigned int m_frameBufferId;
	Texture2D m_colorTexture;
	unsigned int m_depthRenderBufferID;

	int m_prevViewportSettings[4];
};