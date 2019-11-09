#version 330 core

layout(location = 0) in vec3 position;

//uniform mat4 u_mvp;

void main() {
	gl_Position = vec4(position, 1.0);
}