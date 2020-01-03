#version 330 core

out vec3 FragColor;
  
in vec2 vTexCoords;

uniform sampler2D gPosInWorldSpec;
uniform sampler2D gNormalShininess;
uniform sampler2D gAlbedo;
uniform sampler2D u_NoiseMap;

uniform vec3 u_SampleKernel[64];
uniform mat4 u_ViewMat;
uniform mat4 u_NormalMat;
uniform mat4 u_ProjMat;

uniform vec2 u_ScreenResolution;

void main()
{
    if (texture(gAlbedo, vTexCoords).a < 0.95)
        discard;

    vec2 noiseScale = vec2(u_ScreenResolution.x/4.0, u_ScreenResolution.y/4.0); 

    vec3 posInView = (u_ViewMat * vec4(texture(gPosInWorldSpec, vTexCoords).rgb, 1.0)).xyz;
    vec3 normalInView = (u_NormalMat * vec4(texture(gNormalShininess, vTexCoords).rgb, 0.0)).xyz;
    vec3 randomVec = texture(u_NoiseMap, vTexCoords * noiseScale).xyz; 

    vec3 tangent   = normalize(randomVec - normalInView * dot(randomVec, normalInView));
    vec3 bitangent = cross(normalInView, tangent);
    mat3 TBN       = mat3(tangent, bitangent, normalInView); 

    FragColor = randomVec;
}