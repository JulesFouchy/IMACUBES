#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "OpenGL/Texture2D.hpp"

#include "OpenGL/Uniform/Uniform.hpp"

class SSAOcomputer {
public:
	SSAOcomputer();
	void initAfterApp();
	~SSAOcomputer();
	static void Initialize();

	void setSize(int width, int height);

	void compute();
	inline Texture2D& texture() { return m_ambiantOcclusionTexture; }

	void ImGui_Parameters();

private:
	void generateRandomThings();

	void setKernelSize(int newSize);

private:
	Uniform<float> m_radius;
	Uniform<float> m_bias;
	Uniform<float> m_power;
	int m_kernelSize;

	std::vector<glm::vec3> m_sampleKernel;
	std::vector<glm::vec3> m_noiseVectors;
	Texture2D m_noiseTexture;

	unsigned int m_frameBufferID;
	Texture2D m_ambiantOcclusionTexture;

	static size_t SSAOshaderLID;

	static const float m_defaultRadius;
	static const float m_defaultBias;
	static const float m_defaultPower;
	static const int   m_defaultKernelSize;
};