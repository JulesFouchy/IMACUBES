#version 330 core

in vec3 vObjectPos; 
in vec3 vWorldPos;
flat in int vMaterialIndex;

struct MaterialParameters{
	vec3 color; // default  0 0.5 11
	float borderLength; // default 0.1 min 0 max 0.3
	float borderRampEnd; // default 0.5 min 0 max 0.5
};

uniform MaterialParameters params[200];

float ramp(float d){
	MaterialParameters u_ = params[vMaterialIndex];
	return 1.-smoothstep(u_.borderRampEnd - u_.borderLength,u_.borderRampEnd, d);
}

void main() {
	int i = vMaterialIndex;
	float x = ramp(abs(vObjectPos.x));
	float y = ramp(abs(vObjectPos.y));
	float z = ramp(abs(vObjectPos.z));
	float t = min(min(max(x,y), max(x,z)), max(y,z)) ;
	vec3 color = params[i].color * t;
	gl_FragColor = vec4(color,1.0);
}