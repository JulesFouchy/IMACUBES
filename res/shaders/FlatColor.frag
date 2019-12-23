#version 330 core

in vec3 vObjectPos; 
in vec3 vWorldPos;
flat in int vMaterialIndex;

struct MaterialParameters{
	vec3 color; // default  0 0.5 11
};

uniform MaterialParameters params[16];

void main() {
	MaterialParameters u_ = params[vMaterialIndex];
	vec3 color = u_.color;
	gl_FragColor = vec4(color,1.0);
}