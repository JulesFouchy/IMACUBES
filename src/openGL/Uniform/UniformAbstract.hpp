#pragma once

#pragma once

#include <string>

#include "OpenGL/Shader.hpp"
#include "OpenGL/ShaderLibrary.hpp"

#include "Locator/Locate.hpp"

#include "History/HistoryTypes.hpp"

#include "UniformValue.hpp"

class UniformAbstract {
public:
	UniformAbstract(const std::string& name, HistoryType historyType)
		: m_name(name), m_historyType(historyType) {}

	~UniformAbstract() = default;

	virtual void sendTo(Shader& shader, const std::string& name) = 0;
	inline  void sendTo(size_t shaderLID, const std::string& name) { sendTo(GetShader(shaderLID), name); }
	inline  void sendTo(size_t shaderLID) { sendTo(shaderLID, getName()); }

	virtual bool ImGui_Slider() = 0;
	virtual bool ImGui_Drag(float speed = 1.0f) = 0;

	virtual UniformAbstract* createPtrWithSameData() = 0;

	inline const std::string& getName() const { return m_name; }

protected:
	inline static Shader& GetShader(size_t shaderLID) { return Locate::shaderLibrary()[shaderLID]; }

protected:
	std::string m_name;
	HistoryType m_historyType;
};