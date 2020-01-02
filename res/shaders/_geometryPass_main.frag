//? #version 330 core
//? struct MaterialParameters{ float empty; };
//? #include "_geometryPass_uniformsAndVaryings.frag"
//? vec3 albedo() {return vec3(0.);}
// To learn more about these funny comments, see https://marketplace.visualstudio.com/items?itemName=DanielScherzer.GLSL

layout (location = 0) out vec4 gPosInWorld_SpecularIntensity;
layout (location = 1) out vec4 gNormalShininess;
layout (location = 2) out vec4 gAlbedo;

void main() {
	gPosInWorld_SpecularIntensity.rgb = vPosInWorld;
	gNormalShininess.rgb = vNormal;
	gAlbedo = vec4(albedo(), 1.0);
	gNormalShininess.a = lightingProperties[vMaterialIndex].Shininess;
	gPosInWorld_SpecularIntensity.a = lightingProperties[vMaterialIndex].Specular_strength;
}