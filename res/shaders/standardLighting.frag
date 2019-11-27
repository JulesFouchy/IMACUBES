#version 330 core

in vec3 vPos;

uniform float gray;

void main() {
	vec3 color = vec3(gray);//vPos + vec3(0.5);
	gl_FragColor = vec4(color,1.0);
}