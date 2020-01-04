#version 330 core

struct AmbiantLight{
	vec3 color;
	float intensity;
};

struct PointLight{
	vec3 color;
	float intensity;
	vec3 position;
};

struct DirectionalLight{
	vec3 color;
	float intensity;
	vec3 direction;
};

uniform AmbiantLight u_ambiant;
//? const int DEFINE_ME_nbPointLights = 1;
uniform PointLight[DEFINE_ME_nbPointLights] u_points;
const int nbOfPointLights = DEFINE_ME_nbPointLights;
//? const int DEFINE_ME_nbDirectionalLights = 1;
uniform DirectionalLight[DEFINE_ME_nbDirectionalLights] u_directionals;
const int nbOfDirectionalLights = DEFINE_ME_nbDirectionalLights;

uniform sampler2D gPosInWorld_SpecularIntensity;
uniform sampler2D gNormalShininess;
uniform sampler2D gAlbedo;
uniform vec3 u_CamPosInWorld;

uniform bool u_bUseAmbientOcclusion;
uniform sampler2D u_AmbientOcclusionMap;

uniform mat4 u_LightVPMatrices[DEFINE_ME_nbDirectionalLights];
uniform sampler2D u_ShadowMaps[DEFINE_ME_nbDirectionalLights];
uniform float u_ShadowBias;

in vec2 vTexCoords;

float shadow(int dirLightIndex){
	vec4 posInLightSpace = u_LightVPMatrices[dirLightIndex] * vec4(texture(gPosInWorld_SpecularIntensity, vTexCoords).rgb, 1.0);
	vec3 projCoords = posInLightSpace.xyz / posInLightSpace.w;
	if(projCoords.z > 1.0) // we're outside of light's view frustum
        return 1.0;
	projCoords = projCoords * 0.5 + 0.5; 

	float currentDepth = projCoords.z;
	float notShadow = 0.0;
	vec2 texelSize = 1.0 / textureSize(u_ShadowMaps[dirLightIndex], 0);
	for(int x = -1; x <= 1; ++x) {
		for(int y = -1; y <= 1; ++y) {
			float pcfDepth = texture(u_ShadowMaps[dirLightIndex], projCoords.xy + vec2(x, y) * texelSize).r; 
			notShadow += currentDepth - u_ShadowBias > pcfDepth ? 1.0 : 0.0;        
		}    
	}
	notShadow /= 9.0;
	return 1.0 - notShadow;
}

void main(){
	if( texture(gAlbedo, vTexCoords).a < 0.95) // these pixels belong to the clearColor background and shouldn't be lit
		discard;
	vec3  posInWorld = texture(gPosInWorld_SpecularIntensity, vTexCoords).rgb;
	vec3  normal = texture(gNormalShininess, vTexCoords).rgb;
	float specularStrength = texture(gPosInWorld_SpecularIntensity, vTexCoords).a;
	float shininess = texture(gNormalShininess, vTexCoords).a;
	vec3  albedo = texture(gAlbedo, vTexCoords).rgb;

	vec3 camRayReflection = normalize(reflect(posInWorld-u_CamPosInWorld, normal));
	// Ambiant
	vec3 lightColorDiffuse = u_ambiant.color * u_ambiant.intensity * (u_bUseAmbientOcclusion ? texture(u_AmbientOcclusionMap, vTexCoords).r : 1.0);
	vec3 lightColorSpecular = vec3(0.0);
	// Point
	for( int i = 0; i < nbOfPointLights; ++i){
		vec3 lightCol = u_points[i].color * u_points[i].intensity;
		float distSq = dot(u_points[i].position - posInWorld, u_points[i].position - posInWorld);
		float dist = sqrt(distSq);
		vec3 lightDir = (posInWorld - u_points[i].position)/dist;
		// Diffuse
		float dpDiffuse = -dot(normal, lightDir);
		if( dpDiffuse > 0.0 )
			lightColorDiffuse += dpDiffuse / distSq * lightCol;
		// Specular
		float dpSpecular = -dot(camRayReflection, lightDir);
		if( dpSpecular > 0.0 )
			lightColorSpecular += specularStrength * pow(dpSpecular, shininess) / distSq * lightCol;
	}
	// Directional
	for( int i = 0; i < nbOfDirectionalLights; ++i){
		vec3 lightCol = u_directionals[i].color * u_directionals[i].intensity;
		float shadowVal = shadow(i);
		// Diffuse
		float dpDiffuse = -dot(normal, u_directionals[i].direction);
		if( dpDiffuse > 0.0)
			lightColorDiffuse += dpDiffuse * lightCol * shadowVal;
		// Specular
		float dpSpecular = -dot(camRayReflection, u_directionals[i].direction);
		if( dpSpecular > 0.0 )
			lightColorSpecular += specularStrength * pow(dpSpecular, shininess) * lightCol * shadowVal;
	}
	//
	vec3 lightColor = min(lightColorDiffuse, 1.0) + lightColorSpecular;
	gl_FragColor = vec4(albedo * lightColor,1.0);
}