#pragma once

#include <glm/glm.hpp>
#include <string>

#include "OpenGL/UniformUpdateList.hpp"

class Light {
public:
	Light(const std::string& name, const glm::vec3& color = glm::vec3(1.0f), float intensity = 1.0f);
	~Light() = default;

	virtual void setUniforms(const std::string& uniformName, UniformUpdateList & uniformsList);
	virtual void ImGui_Sliders();
	inline const std::string& getName() const { return m_name; }

private:
	std::string m_name;

	glm::vec3 m_color;
	float m_intensity;
};