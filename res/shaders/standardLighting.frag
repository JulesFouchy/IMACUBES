#version 330 core

in vec3 vPos;

uniform float gray; // default 0.4 min 0 max 1
uniform float test34; // default 0.331 min -2 max 2

void main() {
	vec3 color = vec3(gray);//vPos + vec3(0.5);
	gl_FragColor = vec4(color,1.0);
}