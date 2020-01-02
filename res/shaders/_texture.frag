#version 440 core

in vec2 v_TexCoords;

uniform sampler2D u_TextureSlot;

void main() {
	vec4 texColor = texture(u_TextureSlot, v_TexCoords);
	gl_FragColor = texColor;
}