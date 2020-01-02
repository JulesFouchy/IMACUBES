#pragma once

#include "OpenGL/Texture2D.hpp"

class GeometryBuffer {
public:
	GeometryBuffer(int width, int height);
	~GeometryBuffer();

private:
	unsigned int m_frameBufferID;
	Texture2D m_positionTexture;
	Texture2D m_normalShininessTexture;
	Texture2D m_albedoSpecularintensityTexture;
	unsigned int m_depthRenderBufferID;
};