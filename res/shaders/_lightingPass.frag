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
uniform PointLight[16] u_points;
uniform int u_nbOfPointLights;
uniform DirectionalLight[16] u_directionals;
uniform int u_nbOfDirectionalLights;

uniform sampler2D gPosInWorld_SpecularIntensity;
uniform sampler2D gNormalShininess;
uniform sampler2D gAlbedo;
uniform vec3 u_CamPosInWorld;

uniform bool u_bUseAmbientOcclusion;
uniform sampler2D u_AmbientOcclusionMap;

in vec2 vTexCoords;

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
	for( int i = 0; i < u_nbOfPointLights; ++i){
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
	for( int i = 0; i < u_nbOfDirectionalLights; ++i){
		vec3 lightCol = u_directionals[i].color * u_directionals[i].intensity;
		// Diffuse
		float dpDiffuse = -dot(normal, u_directionals[i].direction);
		if( dpDiffuse > 0.0)
			lightColorDiffuse += dpDiffuse * lightCol;
		// Specular
		float dpSpecular = -dot(camRayReflection, u_directionals[i].direction);
		if( dpSpecular > 0.0 )
			lightColorSpecular += specularStrength * pow(dpSpecular, shininess) * lightCol;
	}
	//
	vec3 lightColor = min(lightColorDiffuse, 1.0) + lightColorSpecular;
	gl_FragColor = vec4(albedo * lightColor,1.0);
}