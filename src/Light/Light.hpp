#pragma once

#include <glm/glm.hpp>
#include <string>

#include "OpenGL/Uniform/UniformUpdateList.hpp"
#include "OpenGL/Uniform/UniformConcrete.hpp"

class Light {
friend class LightsManager;
public:
	Light(const std::string& name = "Ambiant Light", const glm::vec3& color = glm::vec3(1.0f), float intensity = 0.45f);
	~Light() = default;

	virtual void setUniforms(const std::string& uniformName, UniformUpdateList & uniformsList);
	virtual void ImGui_Sliders();
	inline const std::string& getName() const { return m_name; }
	inline std::string* getNamePtr() { return &m_name; }

private:
	std::string m_name;

	UniformConcrete<glm::vec3> m_color;
	UniformConcrete<float> m_intensity;
};