#pragma once

#include "UniformValue.hpp"
#include "OpenGL/Shader.hpp"

#include <vector>
#include <unordered_map>
#include <memory>

class UniformUpdateList {
public:
	UniformUpdateList() = default;
	~UniformUpdateList() = default;

	void addSubscriber(size_t shaderLID);
	void sendUniformsTo(size_t shaderLID);

	template <typename T>
	void setUniform(const std::string& uniformName, const T& value) {
		m_uniforms[uniformName] = std::make_unique<UniformValueConcrete<T>>(value);
		updateSubscribersUniform(uniformName);
	}

private:
	void updateSubscribersUniform(const std::string& uniformName);

private:
	std::vector<size_t> m_subscribersLIDs;
	std::unordered_map<std::string, std::unique_ptr<UniformValue>> m_uniforms;
};