#version 330 core

layout(location = 0) in vec3 position;

out vec3 vObjectPos;
out vec3 vWorldPos;

uniform mat4 u_projMat;

void main() {
	vObjectPos = position;
	vWorldPos = position - vec3(0.,-0.8,2.) + gl_InstanceID*vec3(1.0,0.0,0.0);
	gl_Position = u_projMat * vec4(vWorldPos, 1.0);
}