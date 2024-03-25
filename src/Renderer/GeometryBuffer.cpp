#include "GeometryBuffer.hpp"
#include "Debugging/Log.hpp"
#include "Debugging/gl-exception.h"
#include "Locator/Locate.hpp"
#include "Renderer/Renderer.hpp"

GeometryBuffer::GeometryBuffer()
    : m_positionSpecularintensityTexture(GL_RGBA16F, GL_RGBA, GL_FLOAT, GL_NEAREST), m_normalShininessTexture(GL_RGBA16F, GL_RGBA, GL_FLOAT, GL_NEAREST), m_albedoTexture(GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, GL_NEAREST)
{
    // Gen and Bind Framebuffer
    GLCall(glGenFramebuffers(1, &m_frameBufferID));
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID));
    // Texture attachments
    // Position
    m_positionSpecularintensityTexture.bind();
    GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_positionSpecularintensityTexture.getID(), 0));
    // Normal and Shininess
    m_normalShininessTexture.bind();
    GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_normalShininessTexture.getID(), 0));
    // Albedo and Specular intensity
    m_albedoTexture.bind();
    GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, m_albedoTexture.getID(), 0));
    //
    unsigned int attachments[3] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
    GLCall(glDrawBuffers(3, attachments));
    // Depth buffer
    GLCall(glGenRenderbuffers(1, &m_depthRenderBufferID));
    // Unbind
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void GeometryBuffer::setSize(int width, int height)
{
    m_width  = width;
    m_height = height;
    // Resize textures
    m_positionSpecularintensityTexture.initialize(width, height);
    m_normalShininessTexture.initialize(width, height);
    m_albedoTexture.initialize(width, height);
    // Resize depth buffer
    GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_depthRenderBufferID));
    GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height));
    // Reattach
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID));
    GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depthRenderBufferID));
    // Check for completeness
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        spdlog::error("[GeometryBuffer::setSize] Framebuffer is not complete!");
    // Unbind
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

GeometryBuffer::~GeometryBuffer()
{
    GLCall(glDeleteRenderbuffers(1, &m_depthRenderBufferID));
    GLCall(glDeleteFramebuffers(1, &m_frameBufferID));
}

void GeometryBuffer::bind()
{
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID));
}

void GeometryBuffer::unbind()
{
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void GeometryBuffer::copyDepthTo(unsigned int frameBufferID)
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, m_frameBufferID);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBufferID);
    glBlitFramebuffer(0, 0, m_width, m_height, 0, 0, m_width, m_height, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
}