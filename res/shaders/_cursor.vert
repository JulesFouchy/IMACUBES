#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 cubePosition;

out vec3 vPosInObject;

uniform mat4 u_projMat;
uniform mat4 u_viewMat;

void main() {
	vPosInObject = vertexPosition;
	gl_Position = u_projMat * u_viewMat * vec4(vertexPosition + cubePosition, 1.0);
}