#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 cubePosition;
layout(location = 2) in int materialIndex;

out vec3 vObjectPos;
out vec3 vWorldPos;
flat out int vMaterialIndex;

uniform mat4 u_projMat;
uniform mat4 u_viewMat;

void main() {
	vObjectPos = vertexPosition;
	vWorldPos = vertexPosition + cubePosition ; 
	vMaterialIndex = materialIndex;
	gl_Position = u_projMat * u_viewMat * vec4(vWorldPos, 1.0);

}