#include "UniformUpdateList.hpp"

#include "Locator/Locate.hpp"

void UniformUpdateList::addSubscriber(size_t shaderLID) {
	m_subscribersLIDs.push_back(shaderLID);
	setUniformsFor(shaderLID);
}

void UniformUpdateList::setUniformsFor(size_t shaderLID) {
	Locate::shaderLibrary()[shaderLID].bind();
	for (auto& uniform : m_uniforms)
		uniform.second->set(uniform.first, Locate::shaderLibrary()[shaderLID]);
}


void UniformUpdateList::updateSubscribersUniform(const std::string& uniformName) {
	std::unique_ptr<UniformValue>& uniVal = m_uniforms[uniformName];
	for (size_t shaderLID : m_subscribersLIDs) {
		Locate::shaderLibrary()[shaderLID].bind();
		uniVal->set(uniformName, Locate::shaderLibrary()[shaderLID]);
	}
}