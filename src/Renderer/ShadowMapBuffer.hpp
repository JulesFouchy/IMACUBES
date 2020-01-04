#pragma once

#include "OpenGL/Texture2D.hpp"

#include <glm/glm.hpp>

class ShadowMapBuffer {
public:
	ShadowMapBuffer();
	void initAfterApp();
	~ShadowMapBuffer();
	static void Initialize();

	void compute();
	inline Texture2D& texture() { return m_shadowMap; }

private:
	void computeAndSendMatrices();
	void computeViewMat();
	void computeProjMat();

	inline const glm::mat4& getViewMat()     { return m_lightViewMat;}
	inline const glm::mat4& getProjMat()     { return m_lightProjMat;}
	inline const glm::mat4& getViewProjMat() { return m_lightVPMat; }

private:
	unsigned int m_frameBufferID;
	Texture2D m_shadowMap;

	int m_width;
	int m_height;
	float m_nearPlane;
	float m_farPlane;

	glm::mat4 m_lightViewMat;
	glm::mat4 m_lightProjMat;
	glm::mat4 m_lightVPMat;

	static size_t shadowMapShaderLID;
};