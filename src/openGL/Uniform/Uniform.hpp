#pragma once

#include <glad/glad.h>
#include <string>

#include "OpenGL/Shader.hpp"

class Uniform {
public:
	Uniform(Shader* shader, const std::string& name)
		: m_shader(shader), m_name(name)
	{}
	~Uniform() = default;

	virtual void set() = 0;
	
	virtual std::tuple<bool, bool, bool> ImGui_Slider() = 0; // RETURNS : was value modified this frame / did dragging start this frame / did dragging end this frame

	virtual Uniform* createPtrWithSameData() = 0;

	inline const std::string& getName() const { return m_name; }

protected:
	Shader* m_shader;
	std::string m_name;
};