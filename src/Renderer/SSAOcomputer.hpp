#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "OpenGL/Texture2D.hpp"

class SSAOcomputer {
public:
	SSAOcomputer();
	~SSAOcomputer();

	void setSize(int width, int height);

private:
	void generateRandomThings();

private:
	std::vector<glm::vec3> m_sampleKernel;
	std::vector<glm::vec3> m_kernelRotations;
	Texture2D m_rotationsTexture;

	unsigned int m_frameBufferID;
	Texture2D m_ambiantOcclusionTexture;
};