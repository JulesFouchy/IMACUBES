#include "SSAOcomputer.hpp"

#include <random>

#include "Debugging/gl-exception.h"

#include "Helper/Maths.hpp"

#include "Locator/Locate.hpp"
#include "OpenGL/ShaderLibrary.hpp"
#include "Helper/File.hpp"
#include "Renderer.hpp"

size_t SSAOcomputer::SSAOshaderLID;

void SSAOcomputer::Initialize() {
    SSAOshaderLID = Locate::shaderLibrary().LoadShader(MyFile::rootDir + "/res/shaders/_texture.vert", MyFile::rootDir + "/res/shaders/_SSAO.frag");
    Locate::renderer().SSAOmatrixUniforms().addSubscriber(SSAOshaderLID);
}

SSAOcomputer::SSAOcomputer()
    : m_noiseTexture(GL_RGB16F, GL_RGB, GL_FLOAT, GL_NEAREST, GL_REPEAT),
      m_ambiantOcclusionTexture(GL_RED, GL_RGB, GL_FLOAT, GL_NEAREST)
{
    generateRandomThings();
    // Create color attachment
    glGenFramebuffers(1, &m_frameBufferID);
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID);
    m_ambiantOcclusionTexture.bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ambiantOcclusionTexture.getID(), 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

SSAOcomputer::~SSAOcomputer() {
    GLCall(glDeleteFramebuffers(1, &m_frameBufferID));
}

void SSAOcomputer::setSize(int width, int height) {
    m_ambiantOcclusionTexture.setSize(width, height);
}

void SSAOcomputer::generateRandomThings() {
    std::uniform_real_distribution<float> randomFloats(0.0, 1.0);
    std::default_random_engine generator;
    // Sample kernel
    for (int i = 0; i < 64; ++i) {
        glm::vec3 samplePt(
            randomFloats(generator) * 2.0f - 1.0f,
            randomFloats(generator) * 2.0f - 1.0f,
            randomFloats(generator)
        );
        samplePt *= randomFloats(generator) / glm::length(samplePt);
        float scale = i / 64.0f;
        samplePt *= MyMaths::Lerp(0.1f, 1.0f, scale * scale);
        m_sampleKernel.push_back(samplePt);
    }
    // Kernel rotations
    for (int i = 0; i < 16; i++) {
        glm::vec3 rotation(
            randomFloats(generator) * 2.0f - 1.0f,
            randomFloats(generator) * 2.0f - 1.0f,
            0.0f);
        m_noiseVectors.push_back(rotation);
    }
    m_noiseTexture.initialize(4, 4, m_noiseVectors.data());
}

void SSAOcomputer::compute() {
    //GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID));
    Locate::shaderLibrary()[SSAOshaderLID].bind();
    // Attach textures
        // Position map
    Locate::renderer().m_gBuffer.positionSpecularintensityTexture().attachToSlotAndBind();
    Locate::shaderLibrary()[SSAOshaderLID].setUniform1i("gPosInWorldSpec", Locate::renderer().m_gBuffer.positionSpecularintensityTexture().getSlot());
        // Normal map
    Locate::renderer().m_gBuffer.normalShininessTexture().attachToSlotAndBind();
    Locate::shaderLibrary()[SSAOshaderLID].setUniform1i("gNormalShininess", Locate::renderer().m_gBuffer.normalShininessTexture().getSlot());
        // Albedo / Presence map
    Locate::renderer().m_gBuffer.albedoTexture().attachToSlotAndBind();
    Locate::shaderLibrary()[SSAOshaderLID].setUniform1i("gAlbedo", Locate::renderer().m_gBuffer.albedoTexture().getSlot());
        // Noise map
    m_noiseTexture.attachToSlotAndBind();
    Locate::shaderLibrary()[SSAOshaderLID].setUniform1i("u_NoiseMap", m_noiseTexture.getSlot());
    // Send sample kernel
    for(int k = 0; k < m_sampleKernel.size(); ++k)
        Locate::shaderLibrary()[SSAOshaderLID].setUniform3f("u_SampleKernel["+std::to_string(k)+"]", m_sampleKernel[k]);
    // Send screen resolution
    Locate::shaderLibrary()[SSAOshaderLID].setUniform2f("u_ScreenResolution", glm::vec2(Locate::renderer().getWidth(), Locate::renderer().getHeight()));
    // Draw
    Locate::renderer().drawFullScreenQuad();
    // Detach textures
    m_noiseTexture.detachAndUnbind();
    Locate::renderer().m_gBuffer.albedoTexture().detachAndUnbind();
    Locate::renderer().m_gBuffer.normalShininessTexture().detachAndUnbind();
    Locate::renderer().m_gBuffer.positionSpecularintensityTexture().detachAndUnbind();
    //GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}