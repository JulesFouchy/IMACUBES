#version 330 core

in vec3 vPos;

// must be generated so that 2 is replaced by the actual nb of cubes in the group (actually it should be a varying read from a buffer)
//uniform int materialIndices[2];

struct MaterialParameters{
	float bright; // default 0.4 min 0 max 1
	vec3 color; // default  0 0.5 11
	int btb; // default 1 min 0 max 5
};

uniform MaterialParameters params[];


void main() {
	vec3 color = params[0].bright * params[0].color + 0.1*float(params[0].btb);//vPos + vec3(0.5);
	gl_FragColor = vec4(color,1.0);
}