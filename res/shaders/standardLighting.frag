#version 330 core

in vec3 vPos;

void main() {
	vec3 color = vPos + vec3(0.5);
	gl_FragColor = vec4(color,1.0);
}