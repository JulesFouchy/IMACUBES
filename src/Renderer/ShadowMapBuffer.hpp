#pragma once

#include "OpenGL/Texture2D.hpp"

#include <glm/glm.hpp>

#include "OpenGL/Uniform/Uniform.hpp"

class ShadowMapBuffer {
public:
	ShadowMapBuffer();
	ShadowMapBuffer(const ShadowMapBuffer& other) = delete;
	ShadowMapBuffer(ShadowMapBuffer&& other) noexcept;
	void initAfterApp(const glm::vec3& lightDir);
	~ShadowMapBuffer();
	static void Initialize();

	void compute(const glm::vec3& lightDir);
	inline Texture2D& texture() { return m_shadowMap; }

	void ImGui_Parameters();

private:
	void computeAndSendMatrices(const glm::vec3& lightDir);
	void computeViewMat(const glm::vec3& lightDir);
	void computeProjMat();

	inline const glm::mat4& getViewMat()     { return m_lightViewMat;}
	inline const glm::mat4& getProjMat()     { return m_lightProjMat;}
	inline const glm::mat4& getViewProjMat() { return m_lightVPMat; }

	void bind();
	void unbind();

private:
	unsigned int m_frameBufferID;
	Texture2D m_shadowMap;

	int m_width;
	int m_height;
	Uniform<float> m_nearPlane;
	Uniform<float> m_farPlane;
	Uniform<float> m_bias;
	Uniform<float> m_cropFactor;
	Uniform<float> m_lightDistance;

	glm::mat4 m_lightViewMat;
	glm::mat4 m_lightProjMat;
	glm::mat4 m_lightVPMat;

	static size_t shadowMapShaderLID;

	int m_prevViewportSettings[4];
};