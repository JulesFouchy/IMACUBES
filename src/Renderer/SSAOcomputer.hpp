#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "OpenGL/Texture2D.hpp"

class SSAOcomputer {
public:
	SSAOcomputer();
	~SSAOcomputer();
	static void Initialize();

	void setSize(int width, int height);

	void compute();
	inline Texture2D& texture() { return m_ambiantOcclusionTexture; }

private:
	void generateRandomThings();

private:
	std::vector<glm::vec3> m_sampleKernel;
	std::vector<glm::vec3> m_noiseVectors;
	Texture2D m_noiseTexture;

	unsigned int m_frameBufferID;
	Texture2D m_ambiantOcclusionTexture;

	static size_t SSAOshaderLID;
};