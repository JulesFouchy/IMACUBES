#version 330 core

in vec3 vPos;

uniform float gray; // default 0.4 min 0 max 1
uniform float test34; // default 0.331 min -2 max 2
uniform int integgeeeer; // default 17 min -3 max 50
uniform vec3 vector3333; // default  0 0.5 11

void main() {
	vec3 color = gray * vector3333;//vPos + vec3(0.5);
	gl_FragColor = vec4(color,1.0);
}