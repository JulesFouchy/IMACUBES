#version 330 core

//----------------------------------------------------------------------------------------
//----------- All user-defined shaders must give their list of parameters here -----------
//----------------------------------------------------------------------------------------

struct MaterialParameters{
	vec3 Offset; // default 0.740f, 0.179f, 0.179f
	float starIntensity; // default 1.408 min 0 max 2
	float starIntensityPow; // default 1.788 min 0 max 40
	float noiseScale; // default 0 min 0 max 2
	float distortInScale; // default 10.391 min 0 max 60
	float distortOutScale; // default 2.346 min 0 max 60
	vec3 SkyColor; // default 0 0 0
	vec3 StarColor; // default 0.355f, 0.670f, 1.000f
};
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

#include "_uniformsAndVaryings.frag"
// Check the above-included file to know all the informations available (including position in World and Object spaces etc.)

//----------------------------------------------------------------------------------------
//----------- All user-defined shaders must fill in the 'albedo' function ----------------
//----------------------------------------------------------------------------------------

#include "_snoise.frag"
 
vec3 albedo() {
    MaterialParameters u_ = params[vMaterialIndex];
	vec3 uv = vWorldPos + u_.Offset; 
	vec3 color; 
 
	float t = pow(u_.starIntensity * snoise(uv * u_.noiseScale + u_.distortOutScale*snoise(uv*u_.distortInScale)), u_.starIntensityPow); 
	color = mix(u_.SkyColor, u_.StarColor, t);
	return color;
}

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

#include "_main.frag"