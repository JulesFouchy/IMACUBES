#pragma once

#include "OpenGL/Texture2D.hpp"

class GeometryBuffer {
public:
	GeometryBuffer();
	void initialize(int width, int height);
	~GeometryBuffer();

	void bind();
	void unbind();

	inline Texture2D& getPositionTexture() { return m_positionTexture; }
	inline Texture2D& getNormalShininessTexture() { return m_normalShininessTexture; }
	inline Texture2D& getAlbedoSpecularintensityTexture() { return m_albedoSpecularintensityTexture; }

private:
	unsigned int m_frameBufferID;
	Texture2D m_positionTexture;
	Texture2D m_normalShininessTexture;
	Texture2D m_albedoSpecularintensityTexture;
	unsigned int m_depthRenderBufferID;
};