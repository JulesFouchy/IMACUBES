#version 330 core

in vec3 vPos;

// must be generated so that 2 is replaced by the actual nb of cubes in the group (actually it should be a varying read from a buffer)
//uniform int materialIndices[2];

struct MaterialParameters{
float t; // default 0.1 min -1 max 1
	float grayLevel; // default 0.4 min 0 max 1
	vec3 col;
};

uniform MaterialParameters params[];


void main() {
	vec3 color = params[0].col*params[0].t + vec3(params[0].grayLevel)* (vPos + vec3(0.5));
	gl_FragColor = vec4(color,1.0);
}