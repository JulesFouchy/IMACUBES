#pragma once

#include <glad/glad.h>
#include <string>

class Uniform {
public:
	Uniform(GLuint shaderID, const std::string& name)
		: m_shaderID(shaderID), m_name(name), m_location(glGetUniformLocation(shaderID, name.c_str()))
	{}
	~Uniform() = default;

	virtual void set() = 0;
	
	virtual std::tuple<bool, bool, bool> ImGui_Slider() = 0; // RETURNS : was value modified this frame / did dragging start this frame / did dragging end this frame

	virtual Uniform* createPtrWithSameData() = 0;

	inline const std::string& getName() const { return m_name; }
	inline int getLocation() const { return m_location; }

protected:
	GLuint m_shaderID;
	std::string m_name;
	int m_location;
};