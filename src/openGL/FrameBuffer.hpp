#pragma once

#include "Texture2D.hpp"

class FrameBuffer {
public:
    FrameBuffer();
    FrameBuffer(Texture2D& texture);
    ~FrameBuffer();

    void attachTexture(Texture2D& texture);

    void bind();
    void bind_WithoutSettingViewport();
    void setViewport();
    void unbind();
    void unbind_WithoutRestoringViewport();
    void restoreViewport();

    void clear(); // Make sure you have bound the framebuffer beforehand

protected:
    GLuint     m_frameBufferId;
    Texture2D* m_texture;

    int m_prevViewportSettings[4];
};