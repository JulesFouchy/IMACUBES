#include "SSAOcomputer.hpp"

#include <random>

#include "Debugging/gl-exception.h"
#include "Debugging/Log.hpp"

#include "Helper/Maths.hpp"

#include "Locator/Locate.hpp"
#include "OpenGL/ShaderLibrary.hpp"
#include "Helper/File.hpp"
#include "Renderer.hpp"

#include <imgui/imgui.h>

size_t SSAOcomputer::SSAOshaderLID;

void SSAOcomputer::Initialize() {
    SSAOshaderLID = Locate::shaderLibrary().LoadShader(MyFile::rootDir + "/res/shaders/_texture.vert", MyFile::rootDir + "/res/shaders/_SSAO.frag", false);
    Locate::renderer().SSAOmatrixUniforms().addSubscriber(SSAOshaderLID);
}

SSAOcomputer::SSAOcomputer()
    : m_radius("Radius", HistoryType::Lights, 0.805f, 0.001f, 2.0f),
      m_bias("Bias", HistoryType::Lights, 0.05f, 0.001f, 0.1f),
      m_power("Power", HistoryType::Lights, 3.273f, 0.0f, 5.0f),
      m_noiseTexture(GL_RGB16F, GL_RGB, GL_FLOAT, GL_NEAREST, GL_REPEAT),
      m_ambiantOcclusionTexture(GL_RED, GL_RGB, GL_FLOAT, GL_NEAREST)
{
    // Create color attachment
    glGenFramebuffers(1, &m_frameBufferID);
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID);
    m_ambiantOcclusionTexture.bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ambiantOcclusionTexture.getID(), 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void SSAOcomputer::initAfterApp() {
    setKernelSize(32);
}

SSAOcomputer::~SSAOcomputer() {
    GLCall(glDeleteFramebuffers(1, &m_frameBufferID));
}

void SSAOcomputer::setSize(int width, int height) {
    m_ambiantOcclusionTexture.setSize(width, height);
}

void SSAOcomputer::generateRandomThings() {
    m_sampleKernel.clear();
    m_noiseVectors.clear();
    //
    std::uniform_real_distribution<float> randomFloats(0.0, 1.0);
    std::default_random_engine generator;
    // Sample kernel
    for (int i = 0; i < m_kernelSize; ++i) {
        glm::vec3 samplePt(
            randomFloats(generator) * 2.0f - 1.0f,
            randomFloats(generator) * 2.0f - 1.0f,
            randomFloats(generator)
        );
        samplePt *= randomFloats(generator) / glm::length(samplePt);
        float scale = i / (float)m_kernelSize;
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

void SSAOcomputer::setKernelSize(int newSize) {
    m_kernelSize = newSize;
    generateRandomThings();
    Locate::shaderLibrary()[SSAOshaderLID].compile("#KernelSize", std::to_string(m_kernelSize));
    Locate::renderer().SSAOmatrixUniforms().sendUniformsTo(SSAOshaderLID);
}

void SSAOcomputer::compute() {
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID));
    GLCall(glClearColor(0.0, 0.0, 0.0, 0.0));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
    Locate::shaderLibrary()[SSAOshaderLID].bind();
    // Send parameters
    m_radius.sendTo(Locate::shaderLibrary()[SSAOshaderLID], "u_Radius");
    m_bias.sendTo(Locate::shaderLibrary()[SSAOshaderLID], "u_Bias");
    m_power.sendTo(Locate::shaderLibrary()[SSAOshaderLID], "u_Power");
    Locate::shaderLibrary()[SSAOshaderLID].setUniform1i("u_KernelSize", m_kernelSize);
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
    for(int k = 0; k < m_kernelSize; ++k)
        Locate::shaderLibrary()[SSAOshaderLID].setUniform3f("u_SampleKernel["+std::to_string(k)+"]", m_sampleKernel[k]);
    // Send screen resolution
    Locate::shaderLibrary()[SSAOshaderLID].setUniform2f("u_ScreenResolution", glm::vec2(m_ambiantOcclusionTexture.getWidth(), m_ambiantOcclusionTexture.getHeight()));
    // Draw
    Locate::renderer().drawFullScreenQuad();
    // Detach textures
    m_noiseTexture.detachAndUnbind();
    Locate::renderer().m_gBuffer.albedoTexture().detachAndUnbind();
    Locate::renderer().m_gBuffer.normalShininessTexture().detachAndUnbind();
    Locate::renderer().m_gBuffer.positionSpecularintensityTexture().detachAndUnbind();
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void SSAOcomputer::ImGui_Parameters() {
    m_radius.ImGui_Slider();
    m_bias.ImGui_Slider();
    m_power.ImGui_Slider();
    ImGui::SliderInt("Nb of samples", &m_kernelSize, 1, 128);
    if (ImGui::IsItemEdited())
        setKernelSize(m_kernelSize);
}