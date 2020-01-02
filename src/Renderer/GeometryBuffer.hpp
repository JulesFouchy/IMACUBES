#pragma once

#include "OpenGL/Texture2D.hpp"

class GeometryBuffer {
public:
	GeometryBuffer();
	void initialize(int width, int height);
	~GeometryBuffer();

	void bind();
	void unbind();

	void copyDepthTo(unsigned int frameBufferID);

	inline Texture2D& positionTexture() { return m_positionTexture; }
	inline Texture2D& normalShininessTexture() { return m_normalShininessTexture; }
	inline Texture2D& albedoSpecularintensityTexture() { return m_albedoSpecularintensityTexture; }

private:
	int m_width;
	int m_height;
	unsigned int m_frameBufferID;
	Texture2D m_positionTexture;
	Texture2D m_normalShininessTexture;
	Texture2D m_albedoSpecularintensityTexture;
	unsigned int m_depthRenderBufferID;
};