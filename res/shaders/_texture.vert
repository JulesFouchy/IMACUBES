#version 440 core

layout(location = 0) in vec2 fragPosition;
layout(location = 1) in vec2 texCoords;

out vec2 v_TexCoords;

void main() {
	gl_Position = vec4(fragPosition, 0.0, 1.0);
	v_TexCoords = texCoords;
}