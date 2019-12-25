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
uniform PointLight u_point;
uniform DirectionalLight u_directional;

void main() {
	// Ambiant
	vec3 lightColorIntensity = u_ambiant.color * u_ambiant.intensity;
	// Point
	lightColorIntensity += u_point.color * u_point.intensity / length(vWorldPos - u_point.position)/ length(vWorldPos - u_point.position);
	// Directional
	lightColorIntensity += u_directional.color * u_directional.intensity * max(-dot(u_directional.direction, vNormal),0.);
	//
	vec3 lightColor = min(lightColorIntensity, 1.0);
	gl_FragColor = vec4(albedo() * lightColor,1.0);
}