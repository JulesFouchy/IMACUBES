#include "SSAOcomputer.hpp"

#include <random>

#include "Debugging/gl-exception.h"

#include "Helper/Maths.hpp"

SSAOcomputer::SSAOcomputer()
    : m_rotationsTexture(GL_RGB16F, GL_RGB, GL_FLOAT, GL_NEAREST, GL_REPEAT),
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
        m_kernelRotations.push_back(rotation);
    }
    m_rotationsTexture.initialize(4, 4, m_kernelRotations.data());
}