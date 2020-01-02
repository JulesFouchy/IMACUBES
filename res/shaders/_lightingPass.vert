#version 330 core

layout(location = 0) in vec2 aPosInScreen;
layout(location = 1) in vec2 aTexCoords;

out vec2 vTexCoords;

void main() {
	vTexCoords = aTexCoords;
	gl_Position = vec4(aPosInScreen, 0.0, 1.0);
}