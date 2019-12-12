#version 330 core

in vec3 vObjectPos; 
in vec3 vWorldPos;
flat in int vMaterialIndex;

struct MaterialParameters{
	float bright; // default 0.4 min 0 max 1
	vec3 color; // default  0 0.5 11
	int btb; // default 1 min 0 max 5
};

uniform MaterialParameters params[512];


void main() {
	int i = vMaterialIndex;
	vec3 color = params[i].bright * params[i].color + 0.1*float(params[i].btb);//vPos + vec3(0.5);
	gl_FragColor = vec4(color,1.0);
}