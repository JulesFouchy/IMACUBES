#include "Locate.hpp"

#include "App.hpp"

ShaderLibrary& Locate::shaderLibrary() {
	return App::Get().m_shaders;
}