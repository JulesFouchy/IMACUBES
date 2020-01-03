#version 330 core

out float FragColor;
  
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
    float radius = 0.5;
    float bias = 0.025;
    if (texture(gAlbedo, vTexCoords).a < 0.95)
        discard;

    vec2 noiseScale = vec2(u_ScreenResolution.x/4.0, u_ScreenResolution.y/4.0); 

    vec3 posInView = (u_ViewMat * vec4(texture(gPosInWorldSpec, vTexCoords).rgb, 1.0)).xyz;
    vec3 normalInView = normalize((u_NormalMat * vec4(texture(gNormalShininess, vTexCoords).rgb, 0.0)).xyz);
    vec3 randomVec = texture(u_NoiseMap, vTexCoords * noiseScale).xyz; 

    vec3 tangent   = normalize(randomVec - normalInView * dot(randomVec, normalInView));
    vec3 bitangent = cross(normalInView, tangent);
    mat3 TBN       = mat3(tangent, bitangent, normalInView); 

    float occlusion = 0.0;
    for(int i = 0; i < 64; ++i){
        vec3 samplePt = posInView + TBN * u_SampleKernel[i] * radius; 
        vec4 offset = vec4(samplePt, 1.0);
        offset      = u_ProjMat * offset;
        offset.xyz /= offset.w;
        offset.xyz  = offset.xyz * 0.5 + 0.5;
        
        float sampleDepth = (u_ViewMat * vec4(texture(gPosInWorldSpec, offset.xy).xyz, 1.0)).z; 
        float rangeCheck = smoothstep(0.0, 1.0, radius / abs(posInView.z - sampleDepth));
        occlusion += (sampleDepth >= samplePt.z + bias ? 1.0 : 0.0) * rangeCheck;
    } 

    FragColor = 1.0 - (occlusion / 64.0);
}