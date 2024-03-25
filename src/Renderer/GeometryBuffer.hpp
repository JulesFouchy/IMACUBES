#pragma once

#include "OpenGL/Texture2D.hpp"

class GeometryBuffer {
public:
    GeometryBuffer();
    void setSize(int width, int height);
    ~GeometryBuffer();

    void bind();
    void unbind();

    void copyDepthTo(unsigned int frameBufferID);

    inline Texture2D& positionSpecularintensityTexture() { return m_positionSpecularintensityTexture; }
    inline Texture2D& normalShininessTexture() { return m_normalShininessTexture; }
    inline Texture2D& albedoTexture() { return m_albedoTexture; }

private:
    int          m_width;
    int          m_height;
    unsigned int m_frameBufferID;
    Texture2D    m_positionSpecularintensityTexture;
    Texture2D    m_normalShininessTexture;
    Texture2D    m_albedoTexture;
    unsigned int m_depthRenderBufferID;
};