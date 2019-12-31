//? #version 330 core
//? struct MaterialParameters{ float empty; };
//? #include "_uniformsAndVaryings.frag"
//? vec3 albedo() {return vec3(0.);}
// To learn more about these funny comments, see https://marketplace.visualstudio.com/items?itemName=DanielScherzer.GLSL

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

void main() {
	vec3 camRayReflection = normalize(reflect(vPosInWorld-vCamPosInWorld, vNormal));
	// Ambiant
	vec3 lightColorDiffuse = u_ambiant.color * u_ambiant.intensity;
	vec3 lightColorSpecular = vec3(0.0);
	// Point
	for( int i = 0; i < u_nbOfPointLights; ++i){
		vec3 lightCol = u_points[i].color * u_points[i].intensity;
		float distSq = dot(u_points[i].position - vPosInWorld, u_points[i].position - vPosInWorld);
		float dist = sqrt(distSq);
		vec3 lightDir = (vPosInWorld - u_points[i].position)/dist;
		// Diffuse
		float dpDiffuse = -dot(vNormal, lightDir);
		if( dpDiffuse > 0.0 )
			lightColorDiffuse += dpDiffuse / distSq * lightCol;
		// Specular
		float dpSpecular = -dot(camRayReflection, lightDir);
		if( dpSpecular > 0.0 )
			lightColorSpecular += pow(dpSpecular, 32.0) / distSq * lightCol;
	}
	// Directional
	for( int i = 0; i < u_nbOfDirectionalLights; ++i){
		vec3 lightCol = u_directionals[i].color * u_directionals[i].intensity;
		// Diffuse
		float dpDiffuse = -dot(vNormal, u_directionals[i].direction);
		if( dpDiffuse > 0.0)
			lightColorDiffuse += dpDiffuse * lightCol;
		// Specular
		float dpSpecular = -dot(camRayReflection, u_directionals[i].direction);
		if( dpSpecular > 0.0 )
			lightColorSpecular += pow(dpSpecular, 32.0) * lightCol;
	}
	//
	vec3 lightColor = min(lightColorDiffuse, 1.0) + lightColorSpecular;
	gl_FragColor = vec4(albedo() * lightColor,1.0);
}