#version 440 core

in vec2  vTexCoords;
out vec4 fColor;

uniform sampler2D u_TextureSlot;
uniform float     u_DivideColorBy;
uniform float     u_TranslateColorBy;

void main()
{
    vec3 color = vec3(texture(u_TextureSlot, vTexCoords).a) / u_DivideColorBy + vec3(u_TranslateColorBy);
    fColor     = vec4(color, 1.0);
}