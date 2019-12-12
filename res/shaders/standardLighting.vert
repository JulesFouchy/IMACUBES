#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 cubePosition;

out vec3 vObjectPos;
out vec3 vWorldPos;

uniform mat4 u_projMat;
uniform mat4 u_viewMat;

void main() {
	vObjectPos = vertexPosition;
	vWorldPos = vertexPosition + cubePosition ; 
	gl_Position = u_projMat * u_viewMat * vec4(vWorldPos, 1.0);

}