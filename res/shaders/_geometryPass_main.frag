//? #version 330 core
//? struct MaterialParameters{ float empty; };
//? #include "_geometryPass_uniformsAndVaryings.frag"
//? vec3 albedo() {return vec3(0.);}
// To learn more about these funny comments, see https://marketplace.visualstudio.com/items?itemName=DanielScherzer.GLSL

layout (location = 0) out vec3 gPosInWorld;
layout (location = 1) out vec4 gNormalShininess;
layout (location = 2) out vec4 gAlbedoSpec;

void main() {
	gPosInWorld = vPosInWorld;
	gNormalShininess.rgb = vNormal;
	gAlbedoSpec.rgb = albedo();
	gNormalShininess.a = lightingProperties[vMaterialIndex].Shininess;
	gAlbedoSpec.a = lightingProperties[vMaterialIndex].Specular_strength;
}