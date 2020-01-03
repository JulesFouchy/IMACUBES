#version 330 core

out float FragColor;

uniform float u_Radius;
uniform float u_Bias;
uniform float u_Power;
  
in vec2 vTexCoords;

uniform sampler2D gPosInWorldSpec;
uniform sampler2D gNormalShininess;
uniform sampler2D gAlbedo;
uniform sampler2D u_NoiseMap;

uniform mat4 u_ViewMat;
uniform mat4 u_NormalMat;
uniform mat4 u_ProjMat;

uniform vec2 u_ScreenResolution;

//? int #KernelSize = 32
const int KernelSize = #KernelSize;
uniform vec3 u_SampleKernel[#KernelSize];

void main()
{
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
    for(int i = 0; i < KernelSize; ++i){
        vec3 samplePt = posInView + TBN * u_SampleKernel[i] * u_Radius; 
        vec4 offset = vec4(samplePt, 1.0);
        offset      = u_ProjMat * offset;
        offset.xyz /= offset.w;
        offset.xyz  = offset.xyz * 0.5 + 0.5;
        
        float sampleDepth = (u_ViewMat * vec4(texture(gPosInWorldSpec, offset.xy).xyz, 1.0)).z; 
        float rangeCheck = smoothstep(0.0, 1.0, u_Radius / abs(posInView.z - sampleDepth));
        occlusion += (sampleDepth >= samplePt.z + u_Bias ? 1.0 : 0.0) * rangeCheck;
    } 

    FragColor = pow(1.0 - (occlusion / KernelSize), u_Power);
}