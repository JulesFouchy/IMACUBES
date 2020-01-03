#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "OpenGL/Texture2D.hpp"

#include "OpenGL/Uniform/UniformConcrete.hpp"

class SSAOcomputer {
public:
	SSAOcomputer();
	~SSAOcomputer();
	static void Initialize();

	void setSize(int width, int height);

	void compute();
	inline Texture2D& texture() { return m_ambiantOcclusionTexture; }

	void ImGui_ParametersSliders();

private:
	void generateRandomThings();

private:
	UniformConcrete<float> m_radius;
	UniformConcrete<float> m_bias;
	UniformConcrete<float> m_power;

	std::vector<glm::vec3> m_sampleKernel;
	std::vector<glm::vec3> m_noiseVectors;
	Texture2D m_noiseTexture;

	unsigned int m_frameBufferID;
	Texture2D m_ambiantOcclusionTexture;

	static size_t SSAOshaderLID;
};