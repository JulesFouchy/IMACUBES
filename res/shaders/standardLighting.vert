#version 330 core

layout(location = 0) in vec3 position;

out vec3 vPos;

uniform mat4 u_projMat;

void main() {
	vPos = position;
	gl_Position = u_projMat * vec4(position - vec3(0.,0.8,2.) + gl_InstanceID*vec3(1.0,0.0,0.0), 1.0);
}