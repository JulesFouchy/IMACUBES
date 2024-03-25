#pragma once

#include <glm/glm.hpp>
#include <string>
#include "GeometryBuffer.hpp"
#include "OpenGL/FrameBuffer.hpp"
#include "OpenGL/RectVAO.hpp"
#include "OpenGL/Uniform/UniformUpdateList.hpp"
#include "SSAOcomputer.hpp"
#include "ShadowMapBuffer.hpp"

enum class WhatToRender {
    FinalImage,
    AlbedoMap,
    NormalMap,
    PositionMap,
    AmbientOcclusionMap,
    ShadowMap,
    SpecularIntensityMap,
    ShininessMap,
};

struct SDL_Window;

class Renderer {
    friend class App;
    friend class SSAOcomputer;

public:
    Renderer(SDL_Window* window);
    void initAfterApp();
    ~Renderer() = default;

    void drawScene();
    void geometryPass();
    void ssaoPass();
    void shadowPass();
    void lightingPass();
    void renderOnScreenPass();
    void save(int width, int height, const std::string& filepath, int nbSamplesForMSAA = 4);

    void denoiseNormals(Texture2D& texture);
    void blurSSAOtexture(Texture2D& texture);
    void drawOnTexture(Texture2D& texture, Shader& shader);

    void drawFullScreenQuad();

    void onWindowResize();

    void setNumberOfLights(int nbOfPointLights, int nbOfDirectionalLights);

    inline float getWidth() { return m_windowWidth; }
    inline float getHeight() { return m_windowHeight; }
    inline float getRatio() { return m_windowWidth / m_windowHeight; }

    void ImGui_Menu();

private:
    float       m_windowWidth;
    float       m_windowHeight;
    SDL_Window* m_window;

    RectVAO m_fullScreenRect;

    GeometryBuffer m_gBuffer;
    size_t         m_lightingPassShaderLID;
    SSAOcomputer   m_SSAOcomputer;

    WhatToRender m_whatToRender;

    FrameBuffer m_postProcessBuffer;
    size_t      m_denoiseNormalsShaderLID;
    size_t      m_blurSSAOtextureShaderLID;
    bool        m_bDenoiseNormals;
    bool        m_bUseAmbientOcclusion;

    glm::vec4 m_clearColor;
};