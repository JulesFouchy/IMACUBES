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
	// Ambiant
	vec3 lightColorIntensity = u_ambiant.color * u_ambiant.intensity;
	// Point
	for( int i = 0; i < u_nbOfPointLights; ++i){
		float d = dot(normalize(u_points[i].position - vPosInWorld), vNormal);
		// Diffuse
		lightColorIntensity += (d > 0 ? d : 0) * u_points[i].color * u_points[i].intensity / length(vPosInWorld - u_points[i].position) / length(vPosInWorld - u_points[i].position);
	}
	// Directional
	for( int i = 0; i < u_nbOfDirectionalLights; ++i){
		// Diffuse
		lightColorIntensity += u_directionals[i].color * u_directionals[i].intensity * max(-dot(u_directionals[i].direction, vNormal),0.);
	}
	//
	vec3 lightColor = min(lightColorIntensity, 1.0);
	gl_FragColor = vec4(albedo() * lightColor,1.0);
}